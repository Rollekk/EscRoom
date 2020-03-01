// Fill out your copyright notice in the Description page of Project Settings.


#include "HiddenMessagePuzzle.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHiddenMessagePuzzle::AHiddenMessagePuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	RiddleRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Riddle"));
	RiddleRender->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AHiddenMessagePuzzle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHiddenMessagePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

