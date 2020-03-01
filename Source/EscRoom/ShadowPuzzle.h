// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShadowPuzzle.generated.h"

UCLASS()
class ESCROOM_API AShadowPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShadowPuzzle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* RiddleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class AActor* Blockade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FRotator DesiredRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FString")
	FString Riddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boolean")
	bool bIsUnlocked;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool PuzzleSolved();
	bool bIsPuzzleSolved;

	void CheckItem();
	void IsPuzzleUnlocked();

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent* TouchedComponent);
};
