// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "InventoryItem.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APuzzle::APuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	SoundVolume = 0.5f;

	bIsUnlocked = false;
	bOneTime = true;
}

// Called when the game starts or when spawned
void APuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Reward)
	{
		Reward->SetActorEnableCollision(false);
		Reward->SetActorHiddenInGame(true);
	}
}

// Called every frame
void APuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzle::ShowReward()
{
	if (bOneTime)
	{
		Reward->SetActorEnableCollision(true);
		Reward->SetActorHiddenInGame(false);
		UGameplayStatics::PlaySound2D(this, BlockadeSound, SoundVolume);
		bOneTime = false;
	}
}