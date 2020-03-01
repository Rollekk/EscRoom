// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Item.h"
#include "TimerManager.h"

#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
		if (HUDOverlay)
		{
			HUDOverlay->AddToViewport();
			HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if(ItemPickupAsset)
	{
		ItemPickupWidget = CreateWidget<UUserWidget>(this, ItemPickupAsset);
		if (ItemPickupWidget)
		{
			ItemPickupWidget->AddToViewport();
			ItemPickupWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (InspectItemAsset)
	{
		InspectItem = CreateWidget<UUserWidget>(this, InspectItemAsset);
		if (InspectItem)
		{
			InspectItem->AddToViewport();
			InspectItem->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (TextInputAsset)
	{
		TextInput = CreateWidget<UUserWidget>(this, TextInputAsset);
		if (TextInput)
		{
			TextInput->AddToViewport();
			TextInput->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (DialogueAsset)
	{
		Dialogue = CreateWidget<UUserWidget>(this, DialogueAsset);
		if (Dialogue)
		{
			Dialogue->AddToViewport();
			Dialogue->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (PuzzleTipAsset)
	{
		PuzzleTip = CreateWidget<UUserWidget>(this, PuzzleTipAsset);
		if (PuzzleTip)
		{
			PuzzleTip->AddToViewport();
			PuzzleTip->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (LevelNameAsset)
	{
		LevelName = CreateWidget<UUserWidget>(this, LevelNameAsset);
		if (LevelName)
		{
			LevelName->AddToViewport();
			LevelName->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (PauseMenuAsset)
	{
		PauseMenu = CreateWidget<UUserWidget>(this, PauseMenuAsset);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
