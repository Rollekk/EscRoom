// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelNameVolume.generated.h"

UCLASS()
class ESCROOM_API ALevelNameVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelNameVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameInstance")
	class UEscRoomGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
	FString LevelNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bShowed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
		virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void PlayAnimation();
};
