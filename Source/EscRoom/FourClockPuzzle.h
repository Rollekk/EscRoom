// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "FourClockPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API AFourClockPuzzle : public APuzzle
{
	GENERATED_BODY()
	
public:

	AFourClockPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<class AClock*> ArrayOfClocks;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool CheckClocks();

	UFUNCTION()
	void UnlockClock();
};
