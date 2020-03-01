// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorPlate.h"
#include "ColorBall.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

#include "Engine/StaticMeshActor.h"

// Sets default values
AColorPlate::AColorPlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	PlateCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PlateCollision"));
	PlateCollision->SetupAttachment(GetRootComponent());

	bCheckMaterial = false;
	bRevertMaterial = false;
}

// Called when the game starts or when spawned
void AColorPlate::BeginPlay()
{
	Super::BeginPlay();
	PlateCollision->OnComponentBeginOverlap.AddDynamic(this, &AColorPlate::OnBeginOverlap);
	PlateCollision->OnComponentEndOverlap.AddDynamic(this, &AColorPlate::OnEndOverlap);
}

// Called every frame
void AColorPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AColorPlate::CheckPlateCollision()
{
	if (ColorBall->BallMesh->IsOverlappingComponent(PlateCollision))
	{
		ColorBall->bIsInPlace = true;
	}
	else ColorBall->bIsInPlace = false;
}

void AColorPlate::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OverlappedBall = Cast<AColorBall>(OtherActor);
		if (OverlappedBall)
		{
			UMaterialInterface* OverlappedMaterial = OverlappedBall->BallMesh->GetMaterial(2);

			ConnectorMaterial = ConnectorMesh->GetStaticMeshComponent()->GetMaterial(0);

			ConnectorMesh->GetStaticMeshComponent()->SetMaterial(0, OverlappedMaterial);

			bCheckMaterial = true;
			bRevertMaterial = false;
		}
}

void AColorPlate::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
		if (ConnectorMaterial) ConnectorMesh->GetStaticMeshComponent()->SetMaterial(0, ConnectorMaterial);
		bCheckMaterial = false;
		bRevertMaterial = true;
}