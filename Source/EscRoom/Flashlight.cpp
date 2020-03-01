// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashlight.h"
#include "MainCharacter.h"
#include "Backpack.h"
#include "InventoryItem.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundCue.h"


AFlashlight::AFlashlight()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetRootComponent());
	SpotLight->Intensity = 3000.f;
	SpotLight->SetVisibility(false);

	ItemState = EItemState::EIS_Pickup;

	MeshScale = FVector(0.15f);
	SoundVolume = 0.5f;
	bItemParticles = false;
}

void AFlashlight::Equip(AMainCharacter * Main)
{
	OriginalLocation = GetActorLocation();
	OriginalRotation = GetActorRotation();

	if (Main)
	{
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		SkeletalMesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* RightHandSocket = Main->GetMesh()->GetSocketByName("RightHandSocket");
		if (RightHandSocket)
		{
			SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
			SkeletalMesh->SetRelativeRotation(FRotator(0.f));
			SpotLight->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
			SpotLight->SetRelativeRotation(FRotator(90.f));
			SkeletalMesh->SetRelativeScale3D(MeshScale);

			RightHandSocket->AttachActor(this, Main->GetMesh());
			bShouldRotate = false;
			bShouldFloat = false;

			Main->SetEquippedFlashlight(this);
			Main->SetActiveOverlappingItem(nullptr);

			ItemState = EItemState::EIS_Equipped;
		}
		if (OnPickupSound)
		{
			UGameplayStatics::PlaySound2D(this, OnPickupSound, SoundVolume);
		}
		if (!bItemParticles)
		{
			IdleParticlesComponent->Deactivate();
		}

	}
}

void AFlashlight::UnEquip(AMainCharacter * Main)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = Main;

	Main->GetWorld()->SpawnActor<AFlashlight>(SpawnThis,OriginalLocation, OriginalRotation, SpawnInfo);
	SetItemState(EItemState::EIS_Pickup);
	Main->SetEquippedFlashlight(nullptr);
	Main->SetActiveOverlappingItem(nullptr);
}

void AFlashlight::ToggleFlashlight(bool bFClicked)
{
	if (bFClicked)
	{
		SpotLight->SetVisibility(true);
		UGameplayStatics::PlaySound2D(this, FlashlightOnSound, SoundVolume);
	}
	else
	{
		SpotLight->SetVisibility(false);
		UGameplayStatics::PlaySound2D(this, FlashlightOffSound, SoundVolume);
	}
}

void AFlashlight::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if ((ItemState == EItemState::EIS_Pickup) && OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main)
		{
			Main->SetActiveOverlappingItem(this);
		}
	}
}

void AFlashlight::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main)
		{
			Main->SetActiveOverlappingItem(nullptr);
		}
	}
}