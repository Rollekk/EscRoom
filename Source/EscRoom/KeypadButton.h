// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeypadButton.generated.h"

UCLASS()
class ESCROOM_API AKeypadButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeypadButton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MainCharacter")
	class AMainCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* ClickSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	float SoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FString Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	bool isRemove;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent * TouchedComponent);
};
