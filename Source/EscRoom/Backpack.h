// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Backpack.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API ABackpack : public AItem
{
	GENERATED_BODY()
	
public:

	ABackpack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FVector MeshScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | SpawnProperties")
	TSubclassOf<class ABackpack> SpawnThis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* BackpackOpenSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* BackpackCloseSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
	bool bItemParticles;

	void Equip(class AMainCharacter* Main);
	void UnEquip(class AMainCharacter* Main);

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) override;
};
