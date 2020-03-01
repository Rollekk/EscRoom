// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "TablePuzzle.generated.h"

UCLASS()
class ESCROOM_API ATablePuzzle : public APuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATablePuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Table;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Cloth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	class ALeverCollisionBox* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rings")
	TArray<class ATableRing*> RingArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rings")
	FString DesiredWord;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bDestroyComponent;
	bool bSetOneTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool PuzzleSolved();

	void CheckWord();
	void PuzzleShow();
	void IsPuzzleUnlocked();
};
