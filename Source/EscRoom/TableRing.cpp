// Fill out your copyright notice in the Description page of Project Settings.


#include "TableRing.h"
#include "TablePuzzle.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATableRing::ATableRing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring"));
	Ring->SetupAttachment(GetRootComponent());

	RotationValue = 45.f;
	SoundVolume = 0.5f;
}

// Called when the game starts or when spawned
void ATableRing::BeginPlay()
{
	Super::BeginPlay();
	
	Ring->OnBeginCursorOver.AddDynamic(this, &ATableRing::OnPressedMouse);
}

// Called every frame
void ATableRing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATableRing::RingInPlace()
{
	if ((GetActorRotation().Yaw <= DesiredRotation.Yaw + 5) &&
		(GetActorRotation().Yaw >= DesiredRotation.Yaw - 5))
	{
		return true;
	}
	else return false;
}

void ATableRing::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	if (TablePuzzle->bIsUnlocked)
	{
		SetActorRotation(FRotator(0.f, GetActorRotation().Yaw + RotationValue, 0.f));
		UGameplayStatics::PlaySound2D(this, RingRotationSound, SoundVolume);
	}
}

