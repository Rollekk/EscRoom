// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API AInventoryItem : public AItem
{
	GENERATED_BODY()

public:
	AInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem properites")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem properites")
	bool bItemParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem properites")
	bool bIsInInventory;

protected:

public:

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetImage() { return Image; }

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) override;
};
