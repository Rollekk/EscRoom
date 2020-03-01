// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserBeam.generated.h"

UCLASS()
class ESCROOM_API ALaserBeam : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALaserBeam();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Beam;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateBeam(FVector BeamBegin, FVector BeamEnd);
};
