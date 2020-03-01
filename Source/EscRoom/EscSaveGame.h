// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "EscSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float Stamina;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FVector Location;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FRotator Rotation;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString LevelName;

};

/**
 * 
 */
UCLASS()
class ESCROOM_API UEscSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UEscSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FCharacterStats CharacterStats;

};
