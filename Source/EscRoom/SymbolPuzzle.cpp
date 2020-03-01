// Fill out your copyright notice in the Description page of Project Settings.


#include "SymbolPuzzle.h"
#include "Symbol.h"

ASymbolPuzzle::ASymbolPuzzle()
{

	bIsPuzzleSolved = false;
}

void ASymbolPuzzle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASymbolPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Pattern.Len() >= FinalPattern.Len()) CheckPattern();
	if (bIsPuzzleSolved) ShowReward();
}

void ASymbolPuzzle::CheckPattern()
{
	if (Pattern.Equals(*FinalPattern))
	{
		bIsPuzzleSolved = true;
	}
	else
	{
		ResetPattern();
	}
}

void ASymbolPuzzle::ResetPattern()
{
	for (ASymbol* symbol : ArrayOfSymbols)
	{
		if (symbol->bIsOn) symbol->ChangeSymbol();
	}
}
