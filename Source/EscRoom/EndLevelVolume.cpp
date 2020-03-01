// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevelVolume.h"
#include "MainPlayerController.h"
#include "MainCharacter.h"
#include "InventoryItem.h"

#include "KeypadPuzzle.h"
#include "LeverPuzzle.h"
#include "ShadowPuzzle.h"
#include "TablePuzzle.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEndLevelVolume::AEndLevelVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsOverlapping = false;
}

// Called when the game starts or when spawned
void AEndLevelVolume::BeginPlay()
{
	Super::BeginPlay();
	
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

// Called every frame
void AEndLevelVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsOverlapping)
	{
		if (MainCharacter->bItemInInventory)
		{
			MainCharacter->SwitchLevel(LevelName);
		}
	}
}


void AEndLevelVolume::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	bIsOverlapping = true;
	if (MainCharacter) MainCharacter->SetActiveOverlappingCollision(this);
}

void AEndLevelVolume::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (MainCharacter)
	{
		MainCharacter->bItemInInventory = false;
		MainCharacter->SetActiveOverlappingCollision(nullptr);
	}
	bIsOverlapping = false;
}