// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeverCollisionBox.h"
#include "EndLevelVolume.generated.h"

UCLASS()
class ESCROOM_API AEndLevelVolume : public ALeverCollisionBox
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndLevelVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName LevelName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsOverlapping;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) override;
};
