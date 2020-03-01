// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserPuzzle.h"
#include "LaserBeam.h"
#include "LaserSensor.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"
#include "LeverCollisionBox.h"

#include "Components/StaticMeshComponent.h"

ALaserPuzzle::ALaserPuzzle()
{
	PrimaryActorTick.bCanEverTick = true;

	LaserStartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserStartMesh"));
	LaserStartMesh->SetupAttachment(Mesh);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(GetRootComponent());

	bIsMovable = false;
	bIsHitting = false;
	bSpawnBeam = true;
	bIsOn = false;
	bOneTime = true;
	bGetSensorOneTime = true;
}

void ALaserPuzzle::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnBeginCursorOver.AddDynamic(this, &ALaserPuzzle::OnPressedMouse);
}

void ALaserPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHidden) HideBeam();
	else if (bMainLaser) bIsOn = true;

	if (bIsOn && !bHidden)
	{
		DrawLaser();
		bIsMovable = true;
	}
	BlockRotation();
	AllowDeselect();
}

void ALaserPuzzle::HideBeam()
{
	if (bOneTime)
	{
		bIsOn = false;
		if (Beam) Beam->Destroy();
		bSpawnBeam = true;
		bOneTime = false;
		if (LaserSensor) LaserSensor->StopLaserBeam();
		LaserSensor = nullptr;
	}
}

void ALaserPuzzle::CheckSensor()
{
	if (LaserSensor)
	{
		LaserSensor->FireLaserBeam();

		if (LaserSensor->bMainSensor)
		{
			if (LaserSensor->CheckArray())
			{
				if (Reward) ShowReward();
			}
		}
	}
	else
	{
		if (TargetSensor)
		{
			TargetSensor->StopLaserBeam();
			TargetSensor = nullptr;
		}
		bGetSensorOneTime = true;
	}
}

void ALaserPuzzle::DrawLaser()
{
	FHitResult HitResult;

	FVector LineStart = LaserStartMesh->GetComponentLocation();
	FVector LaserForwardVector = LaserStartMesh->GetForwardVector();
	FVector LineEnd = ((LaserForwardVector * LineLength) + LineStart);

	FCollisionQueryParams CollisionParams;
	bIsHitting = GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_GameTraceChannel1, CollisionParams);

	if (bIsHitting)
	{
			FVector BlockLocation = HitResult.ImpactPoint;
			LineEnd = BlockLocation;

			LaserSensor = Cast<ALaserSensor>(HitResult.GetActor());
			if (bGetSensorOneTime)
			{
				TargetSensor = LaserSensor;
				bGetSensorOneTime = false;
			}
			CheckSensor();

	}
	else 
	{
		if (LaserSensor)
		{
			LaserSensor->StopLaserBeam();
			LaserSensor = nullptr;
		}
	}

	if (bSpawnBeam)
	{
		Beam = MainCharacter->GetWorld()->SpawnActor<ALaserBeam>(SpawnThis);
		bSpawnBeam = false;
		bOneTime = true;
	}
	Beam->UpdateBeam(LineStart, LineEnd);
}

void ALaserPuzzle::BlockRotation()
{
	ALeverCollisionBox* Collision = MainCharacter->GetActiveOverlappingCollision();
	if (Collision)
	{
		if (Collision->bChangeCamera)
		{
			MainCharacter->SetObjectToRotate(nullptr);
		}
	}
}

void ALaserPuzzle::AllowDeselect()
{
	if (MainCharacter && MainPlayerController)
	{
		if (MainCharacter->bLMBDown && MainCharacter->GetActiveOverlappingCollision())
		{
			MainPlayerController->bShowMouseCursor = true;
			MainPlayerController->bEnableClickEvents = true;
			MainCharacter->SetObjectToRotate(nullptr);
		}
	}
}

void ALaserPuzzle::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	if (bIsMovable)
	{
		if (MainPlayerController && MainCharacter && MainCharacter->GetActiveOverlappingCollision())
		{
			FInputModeGameOnly InputModeGameOnly;
			MainPlayerController->SetInputMode(InputModeGameOnly);
			MainPlayerController->bShowMouseCursor = false;
			MainCharacter->bShouldTurnRotate = false;
			MainCharacter->SetObjectToRotate(Mesh);
		}
	}
}


