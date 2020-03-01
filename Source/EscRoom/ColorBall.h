// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorBall.generated.h"

UCLASS()
class ESCROOM_API AColorBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorBall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class AMainCharacter* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* BallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ColorPlate")
	class AColorPlate* ColorPlate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bIsInPuzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boolean")
	bool bIsInPlace;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CheckBall();

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent* TouchedComponent);
};
