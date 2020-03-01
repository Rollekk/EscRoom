// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> ItemPickupAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* ItemPickupWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> InspectItemAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* InspectItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> TextInputAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* TextInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> DialogueAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> PuzzleTipAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* PuzzleTip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> PauseMenuAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> LevelNameAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	class UAudioComponent* LevelMusic;

protected:

	virtual void BeginPlay() override;
};
