// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitchPuzzle.h"
#include "MainCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ALightSwitchPuzzle::ALightSwitchPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetupAttachment(GetRootComponent());

	bIsLightOn = true;
}

void ALightSwitchPuzzle::BeginPlay()
{
	Super::BeginPlay();

	ChangeArrays();

	SwitchMesh->OnBeginCursorOver.AddDynamic(this, &ALightSwitchPuzzle::OnPressedMouse);
}

// Called every frame
void ALightSwitchPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightSwitchPuzzle::ChangeArrays()
{
	if (bIsLightOn)
	{
		for (AActor* actors : OffArray)
		{
			actors->SetActorHiddenInGame(true);
			actors->SetActorEnableCollision(false);
		}
		for (AActor* actors : OnArray)
		{
			actors->SetActorHiddenInGame(false);
			actors->SetActorEnableCollision(true);
		}
		bIsLightOn = false;
		SwitchMesh->SetRelativeRotation(FRotator(SwitchMesh->GetComponentRotation().Pitch + 40.f, 90.f, 0.f));
	}
	else
	{
		for (AActor* actors : OnArray)
		{
			actors->SetActorHiddenInGame(true);
			actors->SetActorEnableCollision(false);
		}
		for (AActor* actors : OffArray)
		{
			actors->SetActorHiddenInGame(false);
			actors->SetActorEnableCollision(true);
		}
		bIsLightOn = true;
		SwitchMesh->SetRelativeRotation(FRotator(SwitchMesh->GetComponentRotation().Pitch - 40.f, 90.f, 0.f));
	}
}

void ALightSwitchPuzzle::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	ChangeArrays();
}