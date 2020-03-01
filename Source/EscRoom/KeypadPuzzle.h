// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeypadPuzzle.generated.h"

UCLASS()
class ESCROOM_API AKeypadPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeypadPuzzle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Keypad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spotlight")
	class USpotLightComponent* Spotlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	class UTextRenderComponent* Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle | Sound")
	class USoundCue* AccessDeniedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle | Sound")
	class USoundCue* AccessGrantedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle | Sound")
	class USoundCue* BlockadeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	class AActor* Blockade;

	UPROPERTY(EditAnywhere, Category = "Reward")
	class AInventoryItem* Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle | Sound")
	float SoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	FString TypedCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	FString Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	FString PuzzleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bGrantReward;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector InitialLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrintKeypadCode();
	bool PuzzleSolved();

	bool bIsPuzzleSolved;

	FORCEINLINE void SetCode(FString ToThis) { Code = ToThis;  }
};
