// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeverPuzzle.generated.h"

UCLASS()
class ESCROOM_API ALeverPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALeverPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* LeverStick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* LeverBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Cover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* LeverUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* LeverDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<ALeverPuzzle*> ArrayOfLevers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<ALeverPuzzle*> ArrayOfAllLevers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	class ALeverCollisionBox* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reward")
	class AInventoryItem* Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bIsOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bMainLever;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float SoundVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bOneTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent* TouchedComponent);

	void ToggleLever(ALeverPuzzle* Lever);

	bool PuzzleSolved();
	bool bIsPuzzleSolved;

	FORCEINLINE void SetIsOn(bool bToThis) { bIsOn = bToThis; }
};
