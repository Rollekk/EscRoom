// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ZeroOnePuzzle.generated.h"

UCLASS()
class ESCROOM_API AZeroOnePuzzle : public AItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	class UTextRenderComponent* Number;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timer")
	FTimerHandle Timer;

public:
	// Sets default values for this actor's properties
	AZeroOnePuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<int32> Numbers;
	int32 Iterator;

	bool bStartTimer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeText();

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) override;
};