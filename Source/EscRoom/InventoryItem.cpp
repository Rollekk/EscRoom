// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "MainCharacter.h"

#include "Components/StaticMeshComponent.h"

AInventoryItem::AInventoryItem()
{
	Name = TEXT("DefaultName");
	bIsInInventory = false;

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AInventoryItem::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
	if (Main)
	{
		Main->SetActiveOverlappingItem(this);
	}
}

void AInventoryItem::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
	if (Main)
	{
		Main->SetActiveOverlappingItem(nullptr);
	}
}
