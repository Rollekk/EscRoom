// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorBall.h"
#include "ColorPlate.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"
#include "LeverCollisionBox.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AColorBall::AColorBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMesh;

	bIsInPuzzle = false;
}

// Called when the game starts or when spawned
void AColorBall::BeginPlay()
{
	Super::BeginPlay();
	
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	BallMesh->OnBeginCursorOver.AddDynamic(this, &AColorBall::OnPressedMouse);
}

// Called every frame
void AColorBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckBall();
}

void AColorBall::CheckBall()
{
	if (bIsInPuzzle)
	{
		ColorPlate->CheckPlateCollision();
	}
	
	ALeverCollisionBox* Collision = Cast<ALeverCollisionBox>(MainCharacter->GetActiveOverlappingCollision());
	if(Collision)
	{
		if (Collision->bChangeCamera)
		{
			MainCharacter->SetObjectToMove(nullptr);
		}
	}
}

void AColorBall::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	if (MainPlayerController && MainCharacter && MainCharacter->GetActiveOverlappingCollision())
	{
		FInputModeGameOnly InputModeGameOnly;
		MainPlayerController->SetInputMode(InputModeGameOnly);
		MainPlayerController->bShowMouseCursor = false;
		MainCharacter->SetObjectToMove(BallMesh);
	}
}

