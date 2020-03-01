// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverPuzzle.h"
#include "LeverCollisionBox.h"
#include "InventoryItem.h"

#include "Sound/SoundCue.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALeverPuzzle::ALeverPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComoponent"));
	RootComponent = SceneComponent;

	LeverBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchBody"));
	LeverBody->SetupAttachment(GetRootComponent());

	LeverStick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchStick"));
	LeverStick->SetupAttachment(GetRootComponent());

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetRootComponent());
	SpotLight->LightColor = FColor::Red;
	SpotLight->Intensity = 3000.f;
	SpotLight->OuterConeAngle = 5.f;

	bIsOn = false;
	bMainLever = false;
	bIsPuzzleSolved = false;
	bOneTime = true;

	SoundVolume = 0.5f;

}

// Called when the game starts or when spawned
void ALeverPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	LeverStick->OnBeginCursorOver.AddDynamic(this, &ALeverPuzzle::OnPressedMouse);

	if (bMainLever)
	{
		Reward->SetActorEnableCollision(false);
		Reward->SetActorHiddenInGame(true);
	}
}

// Called every frame
void ALeverPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMainLever)
	{
		if (PuzzleSolved())
		{
			bIsPuzzleSolved = true;
			if (bOneTime && bMainLever)
			{
				Reward->SetActorEnableCollision(true);
				Reward->SetActorHiddenInGame(false);
				bOneTime = false;
			}
			if(bMainLever) CollisionBox->SetActorEnableCollision(true);
		}
		else if (bMainLever) CollisionBox->SetActorEnableCollision(false);
	}
}

void ALeverPuzzle::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	for(ALeverPuzzle* lever : ArrayOfLevers)
	{
		if (lever->bIsOn)
		{
			lever->bIsOn = false;
			UGameplayStatics::PlaySound2D(this, LeverDown, SoundVolume);
		}
		else
		{
			lever->bIsOn = true;
			UGameplayStatics::PlaySound2D(this, LeverUp, SoundVolume);
		}
		ToggleLever(lever);
	}
}

void ALeverPuzzle::ToggleLever(ALeverPuzzle* Lever)
{
	if (Lever->bIsOn)
	{
		Lever->SpotLight->SetLightColor(FColor::Green);
		Lever->LeverStick->SetRelativeRotation(FRotator(40.f, 0.f, 0.f));
	}
	else
	{
		Lever->SpotLight->SetLightColor(FColor::Red);
		Lever->LeverStick->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
	}
}

bool ALeverPuzzle::PuzzleSolved()
{
	for (ALeverPuzzle* lever : ArrayOfAllLevers)
	{
		if (!lever->bIsOn)
		{
			return false;
		}
	}
	return true;
}

