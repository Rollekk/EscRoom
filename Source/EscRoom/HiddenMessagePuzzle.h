// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HiddenMessagePuzzle.generated.h"

UCLASS()
class ESCROOM_API AHiddenMessagePuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHiddenMessagePuzzle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene")
	class USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Text")
	class UTextRenderComponent* RiddleRender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FString Riddle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
