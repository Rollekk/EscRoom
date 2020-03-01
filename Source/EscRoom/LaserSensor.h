// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserSensor.generated.h"

UCLASS()
class ESCROOM_API ALaserSensor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserSensor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* SensorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* GlassMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserPuzzle")
	class ALaserPuzzle* LaserPuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserSensor")
	bool bMainSensor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserSensor")
	TArray<ALaserSensor*> ArrayOfSensors;

protected:

	bool bSensorIsOn;

public:	


	void FireLaserBeam();
	void StopLaserBeam();
	bool CheckArray();
};
