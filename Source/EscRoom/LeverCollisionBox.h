// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeverCollisionBox.generated.h"

UCLASS()
class ESCROOM_API ALeverCollisionBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALeverCollisionBox();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* LeverCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<FString> ArrayOfNeededItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FString")
	FString PuzzleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FString")
	FString FoundItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bIsItemRequired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bShowLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bShowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bShowTipNote;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Array")
	TArray<FString> Tips;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeCamera();
	bool bChangeCamera;

	void SetHideCharacter(bool ShouldHide);
	bool CheckForItem();

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

	FORCEINLINE FString GetPuzzleName() { return PuzzleName; }
};
