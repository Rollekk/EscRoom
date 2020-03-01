// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "ColorPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API AColorPuzzle : public APuzzle
{
	GENERATED_BODY()
	
public:

	AColorPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FRotator DesiredRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bCanMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bMainColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<AColorPuzzle*> ArrayOfColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	class ALightSwitchPuzzle* LightSwitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FString Name;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool PuzzleSolved();
	bool AllPuzzlesSolved();

	bool bIsInPlace;
	bool bIsUnlocked;

	void CheckPuzzle();
	void CheckIfShouldUnlock();
	void UnlockPuzzle();
	void HidePuzzle();
	void ToggleLight();

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent* TouchedComponent);
};
