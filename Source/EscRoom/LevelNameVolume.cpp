// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelNameVolume.h"
#include "MainPlayerController.h"
#include "EscRoomGameInstance.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ALevelNameVolume::ALevelNameVolume()
{

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());

	LevelName = "";
	LevelNumber = "";
}

// Called when the game starts or when spawned
void ALevelNameVolume::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	GameInstance = Cast<UEscRoomGameInstance>(GetGameInstance());

	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ALevelNameVolume::OnEndOverlap);
	bShowed = GameInstance->bShowed;
}

void ALevelNameVolume::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (!bShowed)
	{
		bShowed = true;
		GameInstance->bShowed = bShowed;
		PlayAnimation();
	}
}
