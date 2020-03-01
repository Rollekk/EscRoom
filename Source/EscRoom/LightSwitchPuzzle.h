// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "LightSwitchPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API ALightSwitchPuzzle : public APuzzle
{
	GENERATED_BODY()
	
public:

	ALightSwitchPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* SwitchMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<AActor*> OnArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<AActor*> OffArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsLightOn;
	bool bIsOverlapping;

	void ChangeArrays();

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent * TouchedComponent);
};
