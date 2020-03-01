// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisibleWall.h"
#include "Components/BoxComponent.h"

// Sets default values
AInvisibleWall::AInvisibleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(GetRootComponent());
	SpawningBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpawningBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	SpawningBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SpawningBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera , ECollisionResponse::ECR_Ignore);

	SpawningBox->SetRelativeScale3D(FVector(10.f, 0.2f, 5.f));
}

// Called when the game starts or when spawned
void AInvisibleWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInvisibleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

