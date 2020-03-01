// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverCollisionBox.h"
#include "MainPlayerController.h"
#include "MainCharacter.h"
#include "Backpack.h"
#include "Flashlight.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Blueprint/UserWidget.h"


// Sets default values
ALeverCollisionBox::ALeverCollisionBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	LeverCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("KeypadCamera"));
	LeverCamera->SetupAttachment(GetRootComponent());

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetRootComponent());
	SpotLight->SetVisibility(false);


	bIsItemRequired = false;
	bShowLight = true;
	bShowCamera = true;
	bChangeCamera = true;
}

// Called when the game starts or when spawned
void ALeverCollisionBox::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALeverCollisionBox::OnBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ALeverCollisionBox::OnEndOverlap);
}

// Called every frame
void ALeverCollisionBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALeverCollisionBox::ChangeCamera()
{
	if (MainPlayerController && MainCharacter && bShowCamera)
	{
		if (bChangeCamera)
		{
			MainPlayerController->bShowMouseCursor = true;
			MainPlayerController->bEnableMouseOverEvents = true;

			SetHideCharacter(true);
			MainCharacter->bFreezeCharacter = true;

			PlayerCamera = MainCharacter->Camera;
			PlayerCamera->Deactivate();
			LeverCamera->Activate();
			MainPlayerController->SetViewTargetWithBlend(this);

			if(bShowLight) SpotLight->SetVisibility(true);
			if (bShowTipNote) MainPlayerController->PuzzleTip->SetVisibility(ESlateVisibility::Visible);

			bChangeCamera = false;
		}
		else
		{
			MainPlayerController->bShowMouseCursor = false;
			MainPlayerController->bEnableMouseOverEvents = false;

			SetHideCharacter(false);
			MainCharacter->bFreezeCharacter = false;
			MainCharacter->bItemInInventory = false;
			MainCharacter->bShouldTurnRotate = true;
			MainCharacter->bShouldLookUpRotate = true;
			MainCharacter->bShouldRollRotate = false;

			PlayerCamera = MainCharacter->Camera;
			LeverCamera->Deactivate();
			PlayerCamera->Activate();
			MainPlayerController->SetViewTargetWithBlend(MainCharacter);

			if (bShowTipNote) MainPlayerController->PuzzleTip->SetVisibility(ESlateVisibility::Hidden);
			
			bChangeCamera = true;
		}
	}
}

void ALeverCollisionBox::SetHideCharacter(bool ShouldHide)
{
	MainCharacter->GetMesh()->SetHiddenInGame(ShouldHide);
	if (MainCharacter->EquippedBackpack) MainCharacter->EquippedBackpack->SetActorHiddenInGame(ShouldHide);
	if (MainCharacter->EquippedFlashlight) MainCharacter->EquippedFlashlight->SetActorHiddenInGame(ShouldHide);
}

bool ALeverCollisionBox::CheckForItem()
{
	for (FString name : ArrayOfNeededItems)
	{
		if (MainCharacter->ActiveOverlappingItem->GetFName().Equals(*name))
		{
			FoundItem = *MainCharacter->ActiveOverlappingItem->GetFName();
			return true;
		}
	}
	return false;
}

void ALeverCollisionBox::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (MainCharacter) MainCharacter->SetActiveOverlappingCollision(this);
}

void ALeverCollisionBox::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if(MainCharacter) MainCharacter->SetActiveOverlappingCollision(nullptr);
	if(!bChangeCamera) ChangeCamera();
}
