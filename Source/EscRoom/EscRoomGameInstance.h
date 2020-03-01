// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EscRoomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API UEscRoomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UEscRoomGameInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bNewGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bShowed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	float MusicVolume;
};
