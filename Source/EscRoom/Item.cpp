// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"

#include "Components/SphereComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	IdleParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticlesComponent"));
	IdleParticlesComponent->SetupAttachment(GetRootComponent());

	bShouldRotate = false;
	bShouldFloat = false;

	SoundVolume = 0.5f;
	RotationRate = 45.f;
	Amplitude = 1;
	TimeStretch = 1;
	RunningTime = 0.f;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndOverlap);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate(DeltaTime);
	Float(DeltaTime);
}

void AItem::Rotate(float DeltaTime)
{
	if (bShouldRotate)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += DeltaTime * RotationRate;
		SetActorRotation(Rotation);
	}
}

void AItem::Float(float DeltaTime)
{
	if (bShouldFloat)
	{
		FVector NewLocation = GetActorLocation();

		NewLocation.Z = NewLocation.Z + Amplitude * FMath::Cos(TimeStretch * RunningTime);

		SetActorLocation(NewLocation);
		RunningTime += DeltaTime;
	}
}

void AItem::DestroyItem()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	Rotate(false);
	Float(false);
	bPreviousStateHiG = true;
}

void AItem::Inspect(AItem* Item,class AMainCharacter* Main)
{

		OriginalLocation = Item->GetActorLocation();
		OriginalRotation = Item->GetActorRotation();

		bPreviousStateRotate = Item->GetShouldRotate();
		bPreviousStateFloat = Item->GetShouldFloat();

		Item->SetActorLocation(Main->ObjectInspectSphere->GetComponentLocation());
		Item->SetActorRotation(Main->ObjectInspectSphere->GetComponentRotation());

		Item->SetShouldRotate(false);
		Item->SetShouldFloat(false);
		Item->SetActorHiddenInGame(false);

}

void AItem::StopInspect(AItem * Item, AMainCharacter * Main)
{
	Item->SetActorLocation(OriginalLocation);
	Item->SetActorRotation(OriginalRotation);

	Item->SetShouldRotate(bPreviousStateRotate);
	Item->SetShouldFloat(bPreviousStateFloat);

	if (Item->bPreviousStateHiG)
	{
		Item->DestroyItem();
	}
}

void AItem::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
	if (Main)
	{
		Main->SetActiveOverlappingItem(this);
	}
}

void AItem::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
	if (Main)
	{
		Main->SetActiveOverlappingItem(nullptr);
	}
}