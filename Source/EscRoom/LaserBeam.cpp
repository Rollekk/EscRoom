// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBeam.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALaserBeam::ALaserBeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam"));
	Beam->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ALaserBeam::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaserBeam::UpdateBeam(FVector BeamBegin, FVector BeamEnd)
{
	if (Beam)
	{
		FVector BeamVector = BeamEnd - BeamBegin;
		float BeamScale = BeamVector.Size();

		Beam->SetWorldLocation(BeamBegin);
		Beam->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(BeamVector));

		Beam->SetWorldScale3D(FVector(0.05f, 0.05f, (BeamScale / 100)));
	}
}

