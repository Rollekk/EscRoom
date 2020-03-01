// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorPuzzle.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"
#include "LeverCollisionBox.h"
#include "LightSwitchPuzzle.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/SceneComponent.h"

#include "Kismet/GameplayStatics.h"

AColorPuzzle::AColorPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	Object->SetupAttachment(GetRootComponent());

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(Object);
	SpotLight->SetOuterConeAngle(5.f);
	SpotLight->SetIntensity(5000.f);

	bCanMove = false;
	bMainColor = false;
}

void AColorPuzzle::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Object->OnBeginCursorOver.AddDynamic(this, &AColorPuzzle::OnPressedMouse);
}

// Called every frame
void AColorPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bMainColor) CheckIfShouldUnlock();

	if (bIsUnlocked)
	{
		UnlockPuzzle();
		PuzzleSolved();
		CheckPuzzle();
		ToggleLight();
	}
	else HidePuzzle();
}

bool AColorPuzzle::PuzzleSolved()
{
	if ((Object->GetComponentRotation().Yaw <= (DesiredRotation.Yaw + 5)) && (Object->GetComponentRotation().Yaw >= (DesiredRotation.Yaw - 5)) &&
		(Object->GetComponentRotation().Pitch <= (DesiredRotation.Pitch + 5)) && (Object->GetComponentRotation().Pitch >= (DesiredRotation.Pitch - 5)))
	{
		bIsInPlace = true;
		return true;
	}
	else
	{
		bIsInPlace = false;
		return false;
	}
}

bool AColorPuzzle::AllPuzzlesSolved()
{
	for (AColorPuzzle* color : ArrayOfColors)
	{
		if (!color->bIsInPlace)
		{
			return false;
		}
	}
	return true;
}

void AColorPuzzle::CheckPuzzle()
{
	ALeverCollisionBox* Collision = Cast<ALeverCollisionBox>(MainCharacter->GetActiveOverlappingCollision());
	if (Collision)
	{
		if (Collision->bChangeCamera)
		{
			MainCharacter->SetObjectToRotate(nullptr);
		}
		else
		{
			if (MainCharacter && MainPlayerController)
			{
				if (MainCharacter->bLMBDown)
				{
					MainPlayerController->bShowMouseCursor = true;
					MainPlayerController->bEnableClickEvents = true;
					MainCharacter->SetObjectToRotate(nullptr);
				}
			}
		}
	}

	if (bMainColor)
	{
		if (AllPuzzlesSolved())
		{
			ShowReward();
		}

	}
}

void AColorPuzzle::CheckIfShouldUnlock()
{
	if (MainCharacter)
	{
		ALeverCollisionBox* Collision = MainCharacter->GetActiveOverlappingCollision();
		if (Collision)
		{
			FString PuzzleName = *Collision->GetPuzzleName();
			if (MainCharacter->bItemInInventory && PuzzleName.Equals("ColorPuzzle"))
			{
				for (AColorPuzzle* color : ArrayOfColors)
				{
					if (Collision->FoundItem.Equals(*color->Name))
					{
						color->bIsUnlocked = true;
					}
				}
			}
		}
	}
}

void AColorPuzzle::UnlockPuzzle()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
}

void AColorPuzzle::HidePuzzle()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void AColorPuzzle::ToggleLight()
{
	if (LightSwitch)
	{
		if (LightSwitch->bIsLightOn)
		{
			SpotLight->SetVisibility(true);
		}
		else SpotLight->SetVisibility(false);
	}
}

void AColorPuzzle::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	if (MainPlayerController && MainCharacter && MainCharacter->GetActiveOverlappingCollision())
	{
		if (bCanMove)
		{
			FInputModeGameOnly InputModeGameOnly;
			MainPlayerController->SetInputMode(InputModeGameOnly);
			MainPlayerController->bShowMouseCursor = false;
			MainCharacter->SetObjectToRotate(Object);
			MainCharacter->bShouldRollRotate = true;
			MainCharacter->bShouldLookUpRotate = false;
		}
		else MainCharacter->SetObjectToRotate(nullptr);
	}
}