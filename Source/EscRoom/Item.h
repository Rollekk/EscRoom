// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Pickup UMETA(DisplayName = "Pickup"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),

	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class ESCROOM_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Text")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Text")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Collision")
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Enum")
	EItemState ItemState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
	class UParticleSystemComponent* IdleParticlesComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
	class UParticleSystem* SpawnParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* OnPickupSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	float SoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	bool bShouldRotate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	float RotationRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	bool bShouldFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	FVector OriginalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	FRotator OriginalRotation;

private:

	UPROPERTY(EditAnywhere, Category = "Item | Properties")
	float Amplitude;
	UPROPERTY(EditAnywhere, Category = "Item | Properties")
	float TimeStretch;
	UPROPERTY(EditAnywhere, Category = "Item | Properties")
	float RunningTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bPreviousStateRotate;
	bool bPreviousStateFloat;
	bool bPreviousStateHiG;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Rotate(float DeltaTime);
	void Float(float DeltaTime);
	void DestroyItem();
	void Inspect(AItem* Item,class AMainCharacter* Main);
	void StopInspect(AItem* Item, class AMainCharacter* Main);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	FString GetFName() { return Name; }
	void SetFName(FString ToThis) { Name = ToThis; }

	FORCEINLINE EItemState GetItemStatet() { return ItemState; }
	FORCEINLINE bool GetShouldRotate() { return bShouldRotate;  }
	FORCEINLINE bool GetShouldFloat() { return bShouldFloat;  }

	FORCEINLINE void SetItemState(EItemState State) { ItemState = State; }
	FORCEINLINE void SetShouldRotate(bool ToThis) { bShouldRotate = ToThis; }
	FORCEINLINE void SetShouldFloat(bool ToThis) { bShouldFloat = ToThis; }
};
