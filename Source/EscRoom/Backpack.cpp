// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack.h"
#include "MainCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundCue.h"

ABackpack::ABackpack()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	ItemState = EItemState::EIS_Pickup;

	SoundVolume = 0.5f;
	bItemParticles = false;
}

void ABackpack::Equip(AMainCharacter * Main)
{
	OriginalLocation = GetActorLocation();
	OriginalRotation = GetActorRotation();

	if (Main)
	{
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		SkeletalMesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* BackSocket = Main->GetMesh()->GetSocketByName("BackSocket");
		if (BackSocket)
		{
			SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
			SkeletalMesh->SetRelativeRotation(FRotator(0.f));
			BackSocket->AttachActor(this, Main->GetMesh());
			bShouldRotate = false;
			bShouldFloat = false;

			Main->SetEquippedBackpack(this);
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

void ABackpack::UnEquip(AMainCharacter * Main)
{
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = Main;

	SetItemState(EItemState::EIS_Pickup);
	Main->GetWorld()->SpawnActor<ABackpack>(SpawnThis, OriginalLocation, OriginalRotation, SpawnInfo);
	Main->SetEquippedBackpack(nullptr);
	Main->SetActiveOverlappingItem(nullptr);
}

void ABackpack::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

void ABackpack::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
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
