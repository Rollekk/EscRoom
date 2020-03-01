// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "LaserPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API ALaserPuzzle : public APuzzle
{
	GENERATED_BODY()

public:

	ALaserPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* LaserStartMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	float LineLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	TArray<ALaserPuzzle*> ArrayOfAllLasers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserBeam")
	TSubclassOf<class ALaserBeam> SpawnThis;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LaserSensor")
	class ALaserSensor* LaserSensor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LaserSensor")
	class ALaserSensor* TargetSensor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	bool bMainLaser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	bool bIsOn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ALaserBeam* Beam;
	bool bSpawnBeam;
	bool bOneTime;
	bool bGetSensorOneTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsMovable;
	bool bIsHitting;

	void HideBeam();
	void CheckSensor();
	void DrawLaser();
	void BlockRotation();
	void AllowDeselect();

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent* TouchedComponent);
};
