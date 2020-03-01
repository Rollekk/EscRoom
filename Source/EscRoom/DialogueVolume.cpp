// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueVolume.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/KismetStringLibrary.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

#include "TimerManager.h"

// Sets default values
ADialogueVolume::ADialogueVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bWidgetVisible = false;
	bRestartTimer = true;

	i = 0;
	DialogueToPrint = TEXT("Witaj w grze Escape Room! Jezeli jestes gotow podejdz do drzwi i rozpocznij Swoja przygode.");
}

// Called when the game starts or when spawned
void ADialogueVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADialogueVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(MainPlayerController->Dialogue->IsVisible()) StartDialogue();
}

void ADialogueVolume::StartDialogue()
{
	StringArray = UKismetStringLibrary::GetCharacterArrayFromString(DialogueToPrint);
	DialogueLength = StringArray.Num();
	if (bRestartTimer)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ADialogueVolume::AppendDialogue, 0.02f);
		bRestartTimer = false;
	}
}

void ADialogueVolume::StopDialogue()
{
	bRestartTimer = true;
	FinishedDialogue = "";
	i = 0;
}

void ADialogueVolume::AppendDialogue()
{
	if (i < DialogueLength)
	{
		FinishedDialogue.Append(StringArray[i]);
		i++;
		bRestartTimer = true;
	}
}

void ADialogueVolume::ChangeWidget()
{
	if (bWidgetVisible)
	{
		MainPlayerController->Dialogue->SetVisibility(ESlateVisibility::Hidden);
		StopDialogue();
		bWidgetVisible = false;
	}
	else
	{
		MainPlayerController->Dialogue->SetVisibility(ESlateVisibility::Visible);
		bWidgetVisible = true;
	}
}

void ADialogueVolume::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (MainCharacter) MainCharacter->SetActiveOverlappingCollision(this);
}

void ADialogueVolume::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (MainCharacter) MainCharacter->SetActiveOverlappingCollision(nullptr);
	if (bWidgetVisible) ChangeWidget();
}