// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "MainCharacter.h"
#include "MainPlayerController.h"
#include "EscRoomGameInstance.h"
#include "Backpack.h"
#include "Flashlight.h"
#include "InventoryItem.h"
#include "DialogueVolume.h"
#include "LeverCollisionBox.h"
#include "EscSaveGame.h"
#include "Engine.h"

#include "GameFramework/PlayerController.h"
#include "Gameframework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Sound/SoundCue.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 450.f;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bAbsoluteRotation = true;
	SpringArm->RelativeRotation = FRotator(-10.f, 90.f, 0.f);
	SpringArm->SocketOffset = FVector(0.f, 0.f, 30.f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	ObjectInspectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ObjectInspectSphere"));
	ObjectInspectSphere->SetupAttachment(SpringArm);

	ObjectInspectLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("ObjectInspectLight"));
	ObjectInspectLight->SetupAttachment(ObjectInspectSphere);
	ObjectInspectLight->SetIntensity(500.f);
	ObjectInspectLight->SetVisibility(false);

	NormalSpeed = 500.f;
	SprintingSpeed = 800.f;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	StaminaDrainRate = 25.f;
	MinSprintStamina = 50.f;
	MaxStamina = 150.f;
	ActualStamina = 150.f;
	NumOfArrayElements = 0;

	bFreezeCharacter = false;
	bMovingRight = false;
	bMovingForward = false;
	bSprinting = false;
	bChangeLMB = false;
	bLMBDown = false;

	bFClicked = false;
	bBClicked = false;

	bInteracting = false;
	bIsGameSaved = false;

	bPickedItem = false;
	bIsBackpackOpen = false;

	bItemInInventory = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	bShouldTurnRotate = true;
	bShouldLookUpRotate = true;
	bShouldRollRotate = false;

	ActiveOverlappingCollision = nullptr;

	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;

	RiddleAnswer = "";
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	GameInstance = Cast<UEscRoomGameInstance>(GetGameInstance());
	bNewGame = GameInstance->bNewGame;

	CheckIfSaved();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DeltaStamina = StaminaDrainRate * DeltaTime;
	StaminaBarLogic(DeltaStamina);

	if (bIsCrouched)
	{
		SetMovementStatus(EMovementStatus::EMS_Crouching);
	}
	if (NumOfArrayElements == 0)
	{
		FreeIndicies.Empty();
		Inventory.Empty();
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::StartCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::StopCrouching);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::StopSprinting);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::StopInteracting);

	PlayerInputComponent->BindAction("Inspect", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("Inspect", IE_Released, this, &AMainCharacter::LMBUp);

	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::Drop);

	PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &AMainCharacter::UseEquippedItem);

	PlayerInputComponent->BindAction("OpenInventory", IE_Pressed, this, &AMainCharacter::OpenBackpack);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMainCharacter::ChangeEsc).bExecuteWhenPaused = true;

	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::LookUp);
}

void AMainCharacter::MoveRight(float Value)
{
	bMovingRight = false;

	if (!bFreezeCharacter)
	{
		if ((Controller != nullptr) && (Value != 0.f))
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
			bMovingRight = true;
		}
	}
}

void AMainCharacter::MoveForward(float Value)
{
	bMovingForward = false;
	if (!bFreezeCharacter)
	{
		if ((Controller != nullptr) && (Value != 0.f))
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
			bMovingForward = true;
		}
	}
}

void AMainCharacter::Jump()
{
	if (!bFreezeCharacter) Super::Jump();
}

void AMainCharacter::StopJumping()
{
	Super::StopJumping();
}

void AMainCharacter::StartCrouching()
{
	if (!GetCharacterMovement()->IsFalling() && (!bFreezeCharacter))
	Super::Crouch();
}

void AMainCharacter::StopCrouching()
{
	Super::UnCrouch();
}

void AMainCharacter::Sprint()
{
	if ((MovementStatus != EMovementStatus::EMS_Crouching) && (!bFreezeCharacter)) bSprinting = true;
}

void AMainCharacter::StopSprinting()
{
	bSprinting = false;
}

void AMainCharacter::LMBDown()
{
	bLMBDown = true;

	if (ActiveOverlappingItem)
	{
		if (bChangeLMB)
		{
			HideInspectionHUD();
		}
		else
		{
			ShowInspectionHUD();
		}
	}
}

void AMainCharacter::LMBUp()
{
	bLMBDown = false;
}

void AMainCharacter::Drop()
{
	if (!bFreezeCharacter)
	{
		if(EquippedFlashlight)
		{
			bFClicked = false;
			EquippedFlashlight->UnEquip(this);
			return;
		}
		if(EquippedBackpack)
		{
			CloseBackpack();
			EquippedBackpack->UnEquip(this);
			return;
		}
	}
}

void AMainCharacter::UseEquippedItem()
{
	if (!bFreezeCharacter)
	{
		if (bFClicked)
		{
			bFClicked = false;
		}
		else
		{
			bFClicked = true;
		}
		if (EquippedFlashlight)
			EquippedFlashlight->ToggleFlashlight(bFClicked);
	}
}

void AMainCharacter::OpenBackpack()
{
	if (EquippedBackpack)
	{
		if (bBClicked)
		{
			bBClicked = false;
			bIsBackpackOpen = false;
			if (MainPlayerController && !ActiveOverlappingCollision)
			{
				MainPlayerController->bShowMouseCursor = false;
				FInputModeGameOnly InputModeGameOnly;
				MainPlayerController->SetInputMode(InputModeGameOnly);
			}
			else
			{
				if (ActiveOverlappingCollision->bChangeCamera)
				{
					MainPlayerController->bShowMouseCursor = false;
					FInputModeGameOnly InputModeGameOnly;
					MainPlayerController->SetInputMode(InputModeGameOnly);
				}
			}
			UGameplayStatics::PlaySound2D(this, EquippedBackpack->BackpackCloseSound, EquippedBackpack->SoundVolume);
		}
		else
		{
			bBClicked = true;
			bIsBackpackOpen = true;
			if (MainPlayerController)
			{
				MainPlayerController->bShowMouseCursor = true;
				FInputModeGameAndUI InputModeGameAndUI;
				MainPlayerController->SetInputMode(InputModeGameAndUI);
			}
			UGameplayStatics::PlaySound2D(this, EquippedBackpack->BackpackOpenSound, EquippedBackpack->SoundVolume);
		}
	}
}

void AMainCharacter::Interact()
{
	if (ActiveOverlappingItem && !bFreezeCharacter)
	{
		EquipFlashlight();
		EquipBackpack();
		if(EquippedBackpack) PickupItemToBackpack();
	}
;
	ADialogueVolume* Dialogue = Cast<ADialogueVolume>(ActiveOverlappingCollision);
	if (Dialogue)
	{
		Dialogue->ChangeWidget();
	}
	else
	{
		if(ActiveOverlappingCollision) GetActiveOverlappingCollision()->ChangeCamera();
	}
}

void AMainCharacter::StopInteracting()
{
	bPickedItem = false;
}

void AMainCharacter::OpenPauseMenu()
{
	PlayAnimation();

	MainPlayerController->bShowMouseCursor = true;
	MainPlayerController->bEnableMouseOverEvents = true;
	if (MainPlayerController->LevelMusic) MainPlayerController->LevelMusic->SetPaused(true);

	FInputModeGameAndUI InputModeGameAndUI;
	MainPlayerController->SetInputMode(InputModeGameAndUI);
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	bEscDown = true;
}

void AMainCharacter::ClosePauseMenu()
{
	PlayReverseAnimation();

	MainPlayerController->bShowMouseCursor = false;
	MainPlayerController->bEnableMouseOverEvents = false;
	if(MainPlayerController->LevelMusic) MainPlayerController->LevelMusic->SetPaused(false);

	FInputModeGameOnly InputModeGameOnly;
	MainPlayerController->SetInputMode(InputModeGameOnly);
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	bEscDown = false;
}

void AMainCharacter::ChangeEsc()
{
	{
		if (bEscDown)
		{
			if (MainPlayerController->PauseMenu->IsVisible()) ClosePauseMenu();
		}
		else
		{
			if (!MainPlayerController->PauseMenu->IsVisible()) OpenPauseMenu();
		}
	}
}

void AMainCharacter::Turn(float Value)
{
	if (Value != 0.0)
	{
		if (ActiveOverlappingItem && bChangeLMB)
		{
			ActiveOverlappingItem->AddActorLocalRotation(FRotator(0.f, Value, 0.f));
		}
		if (ItemToRotate)
		{
			if(bShouldTurnRotate)
			ItemToRotate->AddWorldRotation(FRotator(0.f, Value, 0.f));
		}
		if (ItemToMove)
		{
			ItemToMove->AddRelativeLocation(FVector(0.f, -Value, 0.f), true);
		}
	}
}

void AMainCharacter::LookUp(float Value)
{
	if (Value != 0.0)
	{
		if (ActiveOverlappingItem && bChangeLMB)
		{
			ActiveOverlappingItem->AddActorLocalRotation(FRotator(Value, 0.f, 0.f));
		}
		if (ItemToRotate)
		{
			if (bShouldLookUpRotate)
			ItemToRotate->AddWorldRotation(FRotator(Value, 0.f, 0.f));
			else if(bShouldRollRotate)
			ItemToRotate->AddWorldRotation(FRotator(0.f, 0.f, Value));
		}
		if (ItemToMove)
		{
			ItemToMove->AddRelativeLocation(FVector(-Value, 0.f, 0.f), true);
		}
	}
}

void AMainCharacter::RemoveFromBackpack()
{
	if (ActiveOverlappingCollision)
	{ 
		if (ActiveOverlappingCollision->bIsItemRequired)
		{
			if (ActiveOverlappingCollision->CheckForItem())
			{
				AInventoryItem* RemoveThis = Cast<AInventoryItem>(ActiveOverlappingItem);
				int32 ID = Inventory.Find(RemoveThis);
				FreeIndicies.Add(ID);
				RemoveThis->Destroy();
				if (GEngine)
				{
					GEngine->ForceGarbageCollection(true);
				}
				Inventory.RemoveAt(ID);
				Inventory.Insert(nullptr, ID);
				NumOfArrayElements--;
				bItemInInventory = true;
			}
			else
			{
				bItemInInventory = false;
				SetActiveOverlappingItem(nullptr);
			}
		}
	}
	else
	{
		bItemInInventory = false;
		SetActiveOverlappingItem(nullptr);
	}
}

void AMainCharacter::CloseBackpack()
{
	bBClicked = false;
	bIsBackpackOpen = false;
}

void AMainCharacter::SetBackgroundBlur()
{
	Camera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	Camera->PostProcessSettings.bOverride_DepthOfFieldMethod = true;
	Camera->PostProcessSettings.DepthOfFieldFocalDistance = 50.f;
	Camera->PostProcessSettings.DepthOfFieldDepthBlurAmount = 100.f;
	Camera->PostProcessSettings.DepthOfFieldFocalRegion = 110.f;
}

void AMainCharacter::DeleteBackgroundBlur()
{
	Camera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = false;
	Camera->PostProcessSettings.bOverride_DepthOfFieldMethod = false;
	Camera->PostProcessSettings.DepthOfFieldFocalDistance = 0.f;
	Camera->PostProcessSettings.DepthOfFieldDepthBlurAmount = 0.f;
	Camera->PostProcessSettings.DepthOfFieldFocalRegion = 0.f;
}

void AMainCharacter::HideInspectionHUD()
{
	bChangeLMB = false;
	bFreezeCharacter = false;
	ActiveOverlappingItem->StopInspect(ActiveOverlappingItem, this);

	DeleteBackgroundBlur();

	if (MainPlayerController)
	{
		MainPlayerController->InspectItem->SetVisibility(ESlateVisibility::Hidden);
		MainPlayerController->HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		if (bIsBackpackOpen)
		{
			FInputModeGameAndUI InputModeGameAndUI;
			MainPlayerController->SetInputMode(InputModeGameAndUI);
			MainPlayerController->bShowMouseCursor = true;
			SetActiveOverlappingItem(nullptr);
		}
		ObjectInspectLight->SetVisibility(false);
	}
}

void AMainCharacter::SaveGame()
{
		UEscSaveGame* SaveGameInstance = Cast<UEscSaveGame>(UGameplayStatics::CreateSaveGameObject(UEscSaveGame::StaticClass()));

		SaveGameInstance->CharacterStats.Stamina = ActualStamina;
		SaveGameInstance->CharacterStats.MaxStamina = MaxStamina;

		FString MapName = GetWorld()->GetMapName();
		MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

		SaveGameInstance->CharacterStats.LevelName = MapName;

		SaveGameInstance->CharacterStats.Location = GetActorLocation();
		SaveGameInstance->CharacterStats.Rotation = GetActorRotation();

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->PlayerName, SaveGameInstance->UserIndex);
		
		bIsGameSaved = true;
}

void AMainCharacter::LoadGame()
{
	UEscSaveGame* LoadGameInstance = Cast<UEscSaveGame>(UGameplayStatics::CreateSaveGameObject(UEscSaveGame::StaticClass()));

	LoadGameInstance = Cast<UEscSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserIndex));

		GameInstance->bNewGame = false;

		ActualStamina = LoadGameInstance->CharacterStats.Stamina;
		MaxStamina = LoadGameInstance->CharacterStats.MaxStamina;

		SetActorLocation(LoadGameInstance->CharacterStats.Location);
		SetActorRotation(LoadGameInstance->CharacterStats.Rotation);

		SetMovementStatus(EMovementStatus::EMS_Normal);
		GetMesh()->bPauseAnims = false;
		GetMesh()->bNoSkeletonUpdate = false;

		if (LoadGameInstance->CharacterStats.LevelName != TEXT("DefaultLevel"))
		{
			FName LevelName(*LoadGameInstance->CharacterStats.LevelName);

			SwitchLevel(LevelName);
		}
}

void AMainCharacter::LoadGameNoSwitch()
{
	UEscSaveGame* LoadGameInstance = Cast<UEscSaveGame>(UGameplayStatics::CreateSaveGameObject(UEscSaveGame::StaticClass()));

	LoadGameInstance = Cast<UEscSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserIndex));

	if (LoadGameInstance)
	{
		ActualStamina = LoadGameInstance->CharacterStats.Stamina;
		MaxStamina = LoadGameInstance->CharacterStats.MaxStamina;

		SetActorLocation(LoadGameInstance->CharacterStats.Location);
		SetActorRotation(LoadGameInstance->CharacterStats.Rotation);

		SetMovementStatus(EMovementStatus::EMS_Normal);
		GetMesh()->bPauseAnims = false;
		GetMesh()->bNoSkeletonUpdate = false;
	}
}

void AMainCharacter::CheckIfSaved()
{
	UEscSaveGame* LoadGameInstance = Cast<UEscSaveGame>(UGameplayStatics::CreateSaveGameObject(UEscSaveGame::StaticClass()));

	LoadGameInstance = Cast<UEscSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserIndex));

	if (LoadGameInstance)
	{
		bIsGameSaved = true;
		if(!bNewGame) LoadGameNoSwitch();
	}
	else
	{
		bIsGameSaved = false;
	}
}

void AMainCharacter::ShowInspectionHUD()
{
	if (!ActiveOverlappingCollision)
	{
		bChangeLMB = true;
		bFreezeCharacter = true;
		ActiveOverlappingItem->Inspect(ActiveOverlappingItem, this);

		SetBackgroundBlur();

		if (MainPlayerController)
		{
			MainPlayerController->InspectItem->SetVisibility(ESlateVisibility::Visible);
			MainPlayerController->HUDOverlay->SetVisibility(ESlateVisibility::Hidden);
			FInputModeGameOnly InputModeGameOnly;
			MainPlayerController->SetInputMode(InputModeGameOnly);
			MainPlayerController->bShowMouseCursor = false;
			ObjectInspectLight->SetVisibility(true);
		}
	}
	else SetActiveOverlappingItem(nullptr);
}

void AMainCharacter::PickupItemToBackpack()
{
	if (NumOfArrayElements <= 5)
	{
		AInventoryItem* Item = Cast<AInventoryItem>(ActiveOverlappingItem);
		if (Item)
		{
			if (!Item->bIsInInventory)
			{
				PickupItem(Item);
			}
		}
	}
}

void AMainCharacter::EquipFlashlight()
{
	AFlashlight* Flashlight = Cast<AFlashlight>(ActiveOverlappingItem);
	if (Flashlight)
	{
		Flashlight->Equip(this);
		SetActiveOverlappingItem(nullptr);
	}
}

void AMainCharacter::EquipBackpack()
{
	ABackpack* Backpack = Cast<ABackpack>(ActiveOverlappingItem);
	if (Backpack)
	{
		Backpack->Equip(this);
		SetActiveOverlappingItem(nullptr);
	}
}

void AMainCharacter::PickupItem(class AInventoryItem* Item)
{
	bPickedItem = true;
	UGameplayStatics::PlaySound2D(this, Item->OnPickupSound, Item->SoundVolume);
	PickedItem = ActiveOverlappingItem;
	if (FreeIndicies.Num() != 0)
	{
		Inventory[FreeIndicies[0]] = Item;
		FreeIndicies.RemoveAt(0);
	}
	else
	{
		Inventory.Add(Item);
	}
	NumOfArrayElements++;
	Item->DestroyItem();
	Item->bIsInInventory = true;
	SetActiveOverlappingItem(nullptr);
}

void AMainCharacter::SwitchLevel(FName LevelName)
{
	UWorld* World = GetWorld();

	if (World)
	{
		FString CurrentLevel = World->GetMapName();
		CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

		FName CurrentLevelName(*CurrentLevel);


		if (CurrentLevelName != LevelName)
		{
			UGameplayStatics::OpenLevel(World, LevelName);
		}
	}
}

void AMainCharacter::StaminaBarLogic(float DeltaStamina)
{
	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		if (bSprinting)
		{
			if (ActualStamina - DeltaStamina <= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
				ActualStamina -= DeltaStamina;
			}
			else
			{
				if (bMovingForward || bMovingRight)
				{
					ActualStamina -= DeltaStamina;
				}
			}
			if (bMovingForward || bMovingRight)
			{
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
			else
			{
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
		}
		else
		{
			if (ActualStamina + DeltaStamina >= MaxStamina)
			{
				ActualStamina = MaxStamina;
			}
			else
			{
				ActualStamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		} break;

	case EStaminaStatus::ESS_BelowMinimum:
		if (bSprinting)
		{
			if (ActualStamina - DeltaStamina <= 0.f)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				ActualStamina = 0;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else
			{
				if (bMovingForward || bMovingRight)
				{
					SetMovementStatus(EMovementStatus::EMS_Sprinting);
					ActualStamina -= DeltaStamina;
				}
				else
				{
					SetMovementStatus(EMovementStatus::EMS_Normal);
				}
			}
		}
		else
		{
			if (ActualStamina + DeltaStamina >= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				ActualStamina += DeltaStamina;
			}
			else
			{
				ActualStamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		} break;

	case EStaminaStatus::ESS_Exhausted:
		if (bSprinting)
		{
			ActualStamina = 0.f;
		}
		else
		{
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			ActualStamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;

	case EStaminaStatus::ESS_ExhaustedRecovering:

		if (ActualStamina + DeltaStamina >= MinSprintStamina)
		{
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			ActualStamina += DeltaStamina;
		}
		else
		{
			ActualStamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;

	default:
		;
	}
}

void AMainCharacter::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;
	if ((MovementStatus == EMovementStatus::EMS_Sprinting))
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

void AMainCharacter::SetEquippedFlashlight(AFlashlight* FlashlightToSet)
{
	if (EquippedFlashlight)
	{
		EquippedFlashlight->Destroy();
	}
	EquippedFlashlight = FlashlightToSet;
}

void AMainCharacter::SetEquippedBackpack(ABackpack * BackpackToSet)
{
	if (EquippedBackpack)
	{
		EquippedBackpack->Destroy();
	}
	EquippedBackpack = BackpackToSet;
}