// Fill out your copyright notice in the Description page of Project Settings.


#include "Doors.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"
#include "Backpack.h"
#include "Flashlight.h"
#include "InventoryItem.h"
#include "Engine.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Sound/SoundCue.h"
#include "TimerManager.h"

// Sets default values
ADoors::ADoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	bOverlapping = false;
	bCanPlaySoundAgain = true;
}

// Called when the game starts or when spawned
void ADoors::BeginPlay()
{
	Super::BeginPlay();
	
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADoors::OnBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ADoors::OnEndOverlap);

	InitialDoorRotation = GetActorRotation();
}

// Called every frame
void ADoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoors::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (MainCharacter)
	{
		for (AInventoryItem* item : MainCharacter->Inventory)
		{
			item->Destroy();
			MainCharacter->NumOfArrayElements--;
			if (GEngine)
			{
				GEngine->ForceGarbageCollection(true);
			}
		}
		MainCharacter->Inventory.Empty();
		if (MainCharacter->bIsBackpackOpen) MainCharacter->CloseBackpack();
		if (MainCharacter->EquippedBackpack) MainCharacter->EquippedBackpack->UnEquip(MainCharacter);
		if (MainCharacter->EquippedFlashlight) MainCharacter->EquippedFlashlight->UnEquip(MainCharacter);
	}
	OpenDoor();
	if (bCanPlaySoundAgain)
	{
		UGameplayStatics::PlaySound2D(this, DoorOpenSound, SoundVolume);
		bCanPlaySoundAgain = false;
	}
	if(!bOverlapping) bOverlapping = true;
}

void ADoors::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (bOverlapping) bOverlapping = false;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoors::CheckIfOverlapping, 1.f);
}

void ADoors::CheckIfOverlapping()
{
	if (!bOverlapping)
	{
		CloseDoor();
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoors::PlaySound, 0.9f);
	} 
}

void ADoors::PlaySound()
{
	UGameplayStatics::PlaySound2D(this, DoorCloseSound, SoundVolume);
	bCanPlaySoundAgain = true;
}

void ADoors::UpdateDoorRotation(float z)
{
	FRotator NewDoorRotation = InitialDoorRotation;
	NewDoorRotation.Yaw += z;

	SetActorRotation(NewDoorRotation);
}