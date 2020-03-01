// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeverCollisionBox.h"
#include "DialogueVolume.generated.h"

UCLASS()
class ESCROOM_API ADialogueVolume : public ALeverCollisionBox
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	FString FinishedDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	TArray<FString> StringArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	FString DialogueToPrint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;
	int32 i;

	bool bRestartTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartDialogue();
	void StopDialogue();
	void AppendDialogue();

	float DialogueLength;

	void ChangeWidget();
	bool bWidgetVisible;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);
};
