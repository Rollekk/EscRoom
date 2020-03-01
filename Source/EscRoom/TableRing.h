// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TableRing.generated.h"

UCLASS()
class ESCROOM_API ATableRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATableRing();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root component")
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root component")
	class UStaticMeshComponent* Ring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* RingRotationSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class ATablePuzzle* TablePuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boolean")
	FRotator DesiredRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Float")
	float RotationValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Float")
	float SoundVolume;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool RingInPlace();

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent* TouchedComponent);
};
