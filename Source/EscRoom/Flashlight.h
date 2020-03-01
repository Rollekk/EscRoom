// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Flashlight.generated.h"

/**
 * 
 */
UCLASS()
class ESCROOM_API AFlashlight : public AItem
{
	GENERATED_BODY()

public:

	AFlashlight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FVector MeshScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | SpawnProperties")
	TSubclassOf<class AFlashlight> SpawnThis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* FlashlightOnSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* FlashlightOffSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
	bool bItemParticles;

	void Equip(class AMainCharacter* Main);
	void UnEquip(class AMainCharacter* Main);
	void ToggleFlashlight(bool bFClicked);

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) override;

protected:

	FVector OriginalLocation;
	FRotator OriginalRotation;
};
