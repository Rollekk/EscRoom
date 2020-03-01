// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPuzzle.h"
#include "MainPlayerController.h"
#include "LeverCollisionBox.h"
#include "MainCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/SceneComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AShadowPuzzle::AShadowPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	Object->SetupAttachment(GetRootComponent());
	Object->SetVisibility(false);

	RiddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RiddleMesh"));
	RiddleMesh->SetupAttachment(GetRootComponent());

	bIsUnlocked = false;
	bIsPuzzleSolved = false;
}

// Called when the game starts or when spawned
void AShadowPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Object->OnBeginCursorOver.AddDynamic(this, &AShadowPuzzle::OnPressedMouse);
}

// Called every frame
void AShadowPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsUnlocked) CheckItem();
	IsPuzzleUnlocked();
}

bool AShadowPuzzle::PuzzleSolved()
{
	if ((Object->GetComponentRotation().Yaw <= (DesiredRotation.Yaw + 10)) && (Object->GetComponentRotation().Yaw >= (DesiredRotation.Yaw - 10)) &&
		(Object->GetComponentRotation().Roll <= (DesiredRotation.Roll + 10)) && (Object->GetComponentRotation().Roll >= (DesiredRotation.Roll - 10)))
	{
		bIsPuzzleSolved = true;
		return true;
	}
	else return false;
}

void AShadowPuzzle::CheckItem()
{
	if (MainCharacter)
	{
		if (MainCharacter->GetActiveOverlappingCollision())
		{
			ALeverCollisionBox* Collision = Cast<ALeverCollisionBox>(MainCharacter->GetActiveOverlappingCollision());
			FString PuzzleName = *Collision->GetPuzzleName();
			if (MainCharacter->bItemInInventory && PuzzleName.Equals("Shadow"))
			{
				bIsUnlocked = true;
			}
		}
	}
}

void AShadowPuzzle::IsPuzzleUnlocked()
{
	if (MainCharacter)
	{
		ALeverCollisionBox* Collision = Cast<ALeverCollisionBox>(MainCharacter->GetActiveOverlappingCollision());
		if (Collision)
		{
			if (bIsUnlocked)
			{
				Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				Object->SetVisibility(true);

				if (PuzzleSolved())
				{
					if (Blockade) 
					{
						Blockade->SetActorHiddenInGame(true);
						Blockade->SetActorEnableCollision(false);
					}
					Collision->SpotLight->SetLightColor(FColor::Green);
				}
				else
				{
					if (Blockade)
					{
						Blockade->SetActorHiddenInGame(false);
						Blockade->SetActorEnableCollision(true);
					}
					Collision->SpotLight->SetLightColor(FColor::White);
				}
			}
			else
			{
				Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
		else MainCharacter->SetObjectToRotate(nullptr);
	}
}

void AShadowPuzzle::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	if (MainPlayerController && MainCharacter && MainCharacter->GetActiveOverlappingCollision())
	{
		FInputModeGameOnly InputModeGameOnly;
		MainPlayerController->SetInputMode(InputModeGameOnly);
		MainPlayerController->bShowMouseCursor = false;
		MainCharacter->SetObjectToRotate(Object);
	}
}
