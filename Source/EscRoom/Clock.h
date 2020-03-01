// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

UCLASS()
class ESCROOM_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClock();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* ClockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* HourLead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* MinuteLead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FRotator DesiredHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FRotator DesiredMinute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	float RotationValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bIsClockUnlocked;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool LeadInPlace();

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent* TouchedComponent);
};
