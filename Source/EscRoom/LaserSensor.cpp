// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserSensor.h"
#include "LaserPuzzle.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ALaserSensor::ALaserSensor()
{

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	SensorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SensorMesh"));
	SensorMesh->SetupAttachment(GetRootComponent());

	GlassMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlassMesh"));
	GlassMesh->SetupAttachment(GetRootComponent());

	bSensorIsOn = false;
	bMainSensor = false;
}

void ALaserSensor::FireLaserBeam()
{
	if (LaserPuzzle) LaserPuzzle->bIsOn = true;
	bSensorIsOn = true;
}

void ALaserSensor::StopLaserBeam()
{
	if (LaserPuzzle) LaserPuzzle->HideBeam();
	bSensorIsOn = false;
}

bool ALaserSensor::CheckArray()
{
	for (ALaserSensor* sensor : ArrayOfSensors)
	{
		if(!sensor->bSensorIsOn)
		{
			return false;
		}
	}
	return true;
}

