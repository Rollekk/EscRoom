// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeroOnePuzzle.h"
#include "MainCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "TimerManager.h"

// Sets default values
AZeroOnePuzzle::AZeroOnePuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Number = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Number"));
	Number->SetupAttachment(Mesh);

	Numbers = { 7 ,23, 9, 1, 26, 4, 15, 26, 2, 9, 15, 18, 0};
	Iterator = 0;

	bStartTimer = true;

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void AZeroOnePuzzle::BeginPlay()
{
	Super::BeginPlay();

	Number->SetText(FText::AsCultureInvariant(FString::FromInt(Numbers[Iterator])));
}

// Called every frame
void AZeroOnePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStartTimer)
	{
		bStartTimer = false;
		GetWorldTimerManager().SetTimer(Timer, this, &AZeroOnePuzzle::ChangeText, 1.5f);
	}
}

void AZeroOnePuzzle::ChangeText()
{
	Number->SetText(FText::AsCultureInvariant(FString::FromInt(Numbers[Iterator])));

	if (Iterator == (Numbers.Num() - 1))
	{
		Number->SetText(FText::AsCultureInvariant(""));
		Iterator = 0;
	}
	else Iterator++;

	bStartTimer = true;
}

void AZeroOnePuzzle::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AZeroOnePuzzle::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
