// Fill out your copyright notice in the Description page of Project Settings.


#include "BallColorPuzzle.h"
#include "InventoryItem.h"
#include "ColorPlate.h"
#include "ColorBall.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"

#include "Engine/StaticMeshActor.h"
#include "Materials/MaterialInstanceDynamic.h"

ABallColorPuzzle::ABallColorPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationValue = 0.f;
}

void ABallColorPuzzle::BeginPlay()
{
	Super::BeginPlay();
	PotMaterial = PotWater->GetStaticMeshComponent()->GetMaterial(0);
	PotMaterial->GetVectorParameterValue(TEXT("Color"), OriginalPotColor);

}

void ABallColorPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PuzzleSolved()) ShowReward();
	ChangeWaterMaterial();
}

bool ABallColorPuzzle::PuzzleSolved()
{
	for (AColorBall* ball : ArrayOfBalls)
	{
		if (!ball->bIsInPlace && ball->bIsInPuzzle)
		{
			return false;
		}
	}
	return true;
}

void ABallColorPuzzle::ChangeWaterMaterial()
{
	for (AColorPlate* plate : ArrayOfPlates)
	{
		if (plate->OverlappedBall)
		{
			PotMaterial = PotWater->GetStaticMeshComponent()->GetMaterial(0);
			PotMaterial->GetVectorParameterValue(TEXT("Color"), PotColor);

			NewPotMaterial = PotWater->GetStaticMeshComponent()->CreateDynamicMaterialInstance(0, PotMaterial);

			UMaterialInterface* BallMaterial = plate->OverlappedBall->BallMesh->GetMaterial(2);

			BallMaterial->GetVectorParameterValue(TEXT("Color"), BallColor);

			if (plate->bCheckMaterial)
			{
				PotColor += BallColor;
				NewPotMaterial->SetVectorParameterValue(TEXT("Color"), PotColor);

				plate->bCheckMaterial = false;
			}
			if (plate->bRevertMaterial)
			{
				PotColor -= BallColor;
				NewPotMaterial->SetVectorParameterValue(TEXT("Color"), PotColor);

				plate->bRevertMaterial = false;
				plate->OverlappedBall = nullptr;
			}
		}
	}

}
