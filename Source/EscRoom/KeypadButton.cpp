// Fill out your copyright notice in the Description page of Project Settings.


#include "KeypadButton.h"
#include "KeypadPuzzle.h"
#include "MainCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AKeypadButton::AKeypadButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(GetRootComponent());

	isRemove = false;
}

// Called when the game starts or when spawned
void AKeypadButton::BeginPlay()
{
	Super::BeginPlay();
	
	Button->OnBeginCursorOver.AddDynamic(this, &AKeypadButton::OnPressedMouse);
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AKeypadButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeypadButton::OnPressedMouse(UPrimitiveComponent * TouchedComponent)
{
	if (MainCharacter)
	{
		if (!isRemove)
		{
			MainCharacter->AppendKeypadCode(Number);
		}

		FString NewNumber = MainCharacter->GetKeypadCode();
		if (isRemove && !NewNumber.Equals(""))
		{
			NewNumber.RemoveFromEnd(*MainCharacter->GetKeypadCode().Right(1));
			MainCharacter->SetKeypadCode(NewNumber);
		}
		UGameplayStatics::PlaySound2D(this, ClickSound, SoundVolume);
	}
}