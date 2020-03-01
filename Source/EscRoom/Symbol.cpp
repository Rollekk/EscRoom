// Fill out your copyright notice in the Description page of Project Settings.


#include "Symbol.h"
#include "SymbolPuzzle.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/SceneComponent.h"

#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASymbol::ASymbol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	SymbolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SymbolMesh"));
	SymbolMesh->SetupAttachment(GetRootComponent());

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetRootComponent());
	SpotLight->SetOuterConeAngle(5.f);
	SpotLight->SetIntensity(5000.f);
	SpotLight->SetLightColor(FColor::Red);

	OrderNumber = "";

	bIsOn = false;
}

// Called when the game starts or when spawned
void ASymbol::BeginPlay()
{
	Super::BeginPlay();
	
	SymbolMesh->OnBeginCursorOver.AddDynamic(this, &ASymbol::OnPressedMouse);

	OriginalLocation = GetActorLocation();
}

// Called every frame
void ASymbol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SymbolPuzzle->bHidden)
	{
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
	}
	else
	{
		SetActorEnableCollision(true);
		SetActorHiddenInGame(false);
	}
}

void ASymbol::ChangeSymbol()
{
	if (bIsOn)
	{
		SpotLight->SetLightColor(FColor::Red);
		UGameplayStatics::PlaySound2D(this, ReleaseSound,SoundVolume);
		int32 Index = SymbolPuzzle->Pattern.Find(*OrderNumber);
		SymbolPuzzle->Pattern.RemoveAt(Index, 1, true);
		SymbolPuzzle->bIsPuzzleSolved = false;
		ReleaseMesh();
		bIsOn = false;
	}
	else
	{
		SpotLight->SetLightColor(FColor::Green);
		UGameplayStatics::PlaySound2D(this, PushSound, SoundVolume);
		SymbolPuzzle->Pattern.Append(*OrderNumber);
		PushMesh();
		bIsOn = true;
	}
}

void ASymbol::UpdateMesh(float z)
{
	FVector NewMeshLocation = OriginalLocation;
	NewMeshLocation.X += z;

	SetActorLocation(NewMeshLocation);
}

void ASymbol::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	ChangeSymbol();
}