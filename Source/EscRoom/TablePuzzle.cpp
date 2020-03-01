// Fill out your copyright notice in the Description page of Project Settings.


#include "TablePuzzle.h"
#include "TableRing.h"
#include "MainCharacter.h"
#include "LeverCollisionBox.h"
#include "MainPlayerController.h"
#include "LeverCollisionBox.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"

// Sets default values
ATablePuzzle::ATablePuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Table = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Table"));
	Table->SetupAttachment(GetRootComponent());

	Cloth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cloth"));
	Cloth->SetupAttachment(GetRootComponent());

	bIsUnlocked = false;
	bDestroyComponent = true;
	bSetOneTime = true;
	bIsPuzzleSolved = false;

	SoundVolume = 0.5f;

	DesiredWord = "";
}

// Called when the game starts or when spawned
void ATablePuzzle::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CollisionBox->SetActorEnableCollision(false);
}

// Called every frame
void ATablePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bIsUnlocked) CheckWord();
	IsPuzzleUnlocked();
}

bool ATablePuzzle::PuzzleSolved()
{

	for (ATableRing* ring : RingArray)
	{
		if (!ring->RingInPlace())
		{
			return false;
		}
	}
	return true;
}

void ATablePuzzle::CheckWord()
{
	if (MainCharacter)
	{
		if (MainCharacter->GetActiveOverlappingCollision())
		{
			ALeverCollisionBox* Collision = Cast<ALeverCollisionBox>(MainCharacter->GetActiveOverlappingCollision());
			FString PuzzleName = *Collision->GetPuzzleName();
			if (PuzzleName.Equals("Table"))
			{
				if (MainPlayerController)
				{
					if(!Collision->bChangeCamera) MainPlayerController->TextInput->SetVisibility(ESlateVisibility::Visible);
					if (MainCharacter->RiddleAnswer.ToLower().Equals(DesiredWord))
					{
						bIsUnlocked = true;
						MainPlayerController->TextInput->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}
			if (Collision->bChangeCamera) MainPlayerController->TextInput->SetVisibility(ESlateVisibility::Hidden);
		}
		else MainPlayerController->TextInput->SetVisibility(ESlateVisibility::Hidden);

	}
}

void ATablePuzzle::PuzzleShow()
{
		Cloth->DestroyComponent();

		for (ATableRing* ring : RingArray)
		{
			ring->Ring->SetVisibility(true);
		}
		bDestroyComponent = false;
}

void ATablePuzzle::IsPuzzleUnlocked()
{
	if (bIsUnlocked)
	{
		if(bDestroyComponent) PuzzleShow();
		if (PuzzleSolved())
		{
			if (bSetOneTime)
			{
				CollisionBox->SetActorEnableCollision(true);
				UGameplayStatics::PlaySound2D(this, BlockadeSound, SoundVolume);
				bSetOneTime = false;
				bIsPuzzleSolved = true;
			}

		}
		else
		{
			CollisionBox->SetActorEnableCollision(false);
			bSetOneTime = true;
		}
	}
	else
	{
		for (ATableRing* ring : RingArray)
		{
			ring->Ring->SetVisibility(false);
		}
	}
}

