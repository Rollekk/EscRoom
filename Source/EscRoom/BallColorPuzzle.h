// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "BallColorPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API ABallColorPuzzle : public APuzzle
{
	GENERATED_BODY()
	
public:

	ABallColorPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<class AColorBall*> ArrayOfBalls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<class AColorPlate*> ArrayOfPlates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	class AStaticMeshActor* PotWater;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material")
	UMaterialInterface* PotMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material")
	UMaterialInstanceDynamic* NewPotMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LinearColor")
	FLinearColor BallColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LinearColor")
	FLinearColor PotColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LinearColor")
	FLinearColor OriginalPotColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool PuzzleSolved();
	void ChangeWaterMaterial();
};
