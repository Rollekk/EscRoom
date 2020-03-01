// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "SymbolPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API ASymbolPuzzle : public APuzzle
{
	GENERATED_BODY()
	
public:

	ASymbolPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pattern")
	FString FinalPattern;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pattern")
	FString Pattern;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<class ASymbol*> ArrayOfSymbols;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsPuzzleSolved;

	void CheckPattern();
	void ResetPattern();
};
