// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Doors.generated.h"

UCLASS()
class ESCROOM_API ADoors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoors();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* DoorOpenSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* DoorCloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float SoundVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;
	FRotator InitialDoorRotation;

	bool bOverlapping;
	bool bCanPlaySoundAgain;

	void PlaySound();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OpenDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void CloseDoor();

	void CheckIfOverlapping();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void UpdateDoorRotation(float z);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);
};
