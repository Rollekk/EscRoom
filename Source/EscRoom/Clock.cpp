// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	ClockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClockMesh"));
	ClockMesh->SetupAttachment(GetRootComponent());
	ClockMesh->SetVisibility(false);

	HourLead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HourLead"));
	HourLead->SetupAttachment(GetRootComponent());
	HourLead->SetVisibility(false);

	MinuteLead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinuteLead"));
	MinuteLead->SetupAttachment(GetRootComponent());
	MinuteLead->SetVisibility(false);

	Name = TEXT("");

	bIsClockUnlocked = false;
}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();
	
	HourLead->OnBeginCursorOver.AddDynamic(this, &AClock::OnPressedMouse);
	MinuteLead->OnBeginCursorOver.AddDynamic(this, &AClock::OnPressedMouse);

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsClockUnlocked)
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
}

bool AClock::LeadInPlace()
{
	if ((HourLead->GetComponentRotation().Roll <= DesiredHour.Roll + 5) &&
		(HourLead->GetComponentRotation().Roll >= DesiredHour.Roll - 5) &&
		(MinuteLead->GetComponentRotation().Roll <= DesiredMinute.Roll + 5) &&
		(MinuteLead->GetComponentRotation().Roll >= DesiredMinute.Roll - 5))
	{
		return true;
	}
	else return false;
}

void AClock::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	TouchedComponent->SetRelativeRotation(FRotator(0.f, 0.f, TouchedComponent->GetComponentRotation().Roll + RotationValue));
}

