// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvisibleWall.generated.h"

UCLASS()
class ESCROOM_API AInvisibleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInvisibleWall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoxComponent")
	class UBoxComponent* SpawningBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
