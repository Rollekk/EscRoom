// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.generated.h"

UCLASS()
class ESCROOM_API APuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class AMainCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	class AInventoryItem* Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* BlockadeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockade")
	class AActor* Blockade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float SoundVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unlock")
	bool bIsUnlocked;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bOneTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsPuzzleSolved = false;

	void ShowReward();
};
