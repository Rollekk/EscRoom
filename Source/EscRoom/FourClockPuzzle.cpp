// Fill out your copyright notice in the Description page of Project Settings.


#include "FourClockPuzzle.h"
#include "Clock.h"
#include "MainCharacter.h"
#include "LeverCollisionBox.h"
#include "InventoryItem.h"

AFourClockPuzzle::AFourClockPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFourClockPuzzle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFourClockPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UnlockClock();
	if (CheckClocks())
	{
		ShowReward();
	}
}

bool AFourClockPuzzle::CheckClocks()
{
	for (AClock* clock : ArrayOfClocks)
	{
		if (clock->bIsClockUnlocked)
		{
			if (!clock->LeadInPlace())
			{
				return false;
			}
		}
		else return false;
	}
	return true;
}

void AFourClockPuzzle::UnlockClock()
{
	if (MainCharacter)
	{
		ALeverCollisionBox* Collision = MainCharacter->GetActiveOverlappingCollision();
		if (Collision)
		{
			FString PuzzleName = *Collision->GetPuzzleName();
			if (MainCharacter->bItemInInventory && PuzzleName.Equals("ClockPuzzle"))
			{
				for (AClock* clock : ArrayOfClocks)
				{
					if (Collision->FoundItem.Equals(*clock->Name))
					{
						clock->bIsClockUnlocked = true;
					}
				}
			}
		}
	}
}
