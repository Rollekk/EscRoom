// Fill out your copyright notice in the Description page of Project Settings.


#include "KeypadPuzzle.h"
#include "MainPlayerController.h"
#include "LeverCollisionBox.h"
#include "MainCharacter.h"
#include "InventoryItem.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AKeypadPuzzle::AKeypadPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Keypad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Keypad"));
	Keypad->SetupAttachment(GetRootComponent());

	Spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	Spotlight->SetupAttachment(GetRootComponent());
	Spotlight->LightColor = FColor::Red;
	Spotlight->Intensity = 3000.f;
	Spotlight->OuterConeAngle = 5.f;

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetupAttachment(GetRootComponent());

	bGrantReward = false;
	bIsPuzzleSolved = false;

	PuzzleName = "";
}

// Called when the game starts or when spawned
void AKeypadPuzzle::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(Reward) Reward->SetActorEnableCollision(false);
	if(Blockade) Blockade->SetActorHiddenInGame(false);
}

// Called every frame
void AKeypadPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PrintKeypadCode();
	PuzzleSolved();
}

void AKeypadPuzzle::PrintKeypadCode()
{
	if (MainCharacter)
	{
		TypedCode = MainCharacter->GetKeypadCode();
		if (TypedCode.Len() <= 4)
		{
			Text->SetText(FText::AsCultureInvariant(TypedCode));
		}
		else
		{
			MainCharacter->SetKeypadCode("");
			UGameplayStatics::PlaySound2D(this, AccessDeniedSound, SoundVolume);
		}
	}
}

bool AKeypadPuzzle::PuzzleSolved()
{
	if (MainCharacter)
	{
		ALeverCollisionBox* Collision = Cast<ALeverCollisionBox>(MainCharacter->GetActiveOverlappingCollision());
		if (Collision && Collision->PuzzleName.Equals(PuzzleName))
		{
			if (TypedCode.Equals(*Code))
			{
				if (Blockade) Blockade->SetActorHiddenInGame(true);
				if (Reward) Reward->SetActorEnableCollision(true);
				Spotlight->SetLightColor(FColor::Green);
				UGameplayStatics::PlaySound2D(this, AccessGrantedSound, SoundVolume);
				UGameplayStatics::PlaySound2D(this, BlockadeSound, SoundVolume);
				MainCharacter->SetKeypadCode("");
				bIsPuzzleSolved = true;
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}