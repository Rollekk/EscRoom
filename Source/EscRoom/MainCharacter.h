// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_Crouching UMETA(DisplayName = "Crouching"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class ESCROOM_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enum")
	EStaminaStatus StaminaStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enum")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameInstance")
	class UEscRoomGameInstance* GameInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light")
	class USpotLightComponent* ObjectInspectLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* ObjectInspectSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActiveOverlappingItem")
	class AItem* ActiveOverlappingItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	class ALeverCollisionBox* ActiveOverlappingCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickedItem")
	class AItem* PickedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	class AFlashlight* EquippedFlashlight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Backpack")
	class ABackpack* EquippedBackpack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotate")
	class UStaticMeshComponent* ItemToRotate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Move")
	class UStaticMeshComponent* ItemToMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaDrainRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MinSprintStamina;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float ActualStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float NormalSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintingSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class AInventoryItem*> Inventory;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<int32> FreeIndicies;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 NumOfArrayElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	FString KeypadCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Answer")
	FString RiddleAnswer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool bFreezeCharacter;
	bool bItemInInventory;

	void MoveRight(float Value);
	bool bMovingRight;

	void MoveForward(float Value);
	bool bMovingForward;

	void Jump();
	void StopJumping();

	void StartCrouching();
	void StopCrouching();

	void Sprint();
	void StopSprinting();
	bool bSprinting;

	UFUNCTION(BlueprintCallable)
	void LMBDown();
	void LMBUp();
	bool bChangeLMB;
	bool bLMBDown;

	void Drop();

	void UseEquippedItem();
	bool bFClicked;

	void OpenBackpack();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boolean")
	bool bBClicked;

	void Interact();
	void StopInteracting();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bPickedItem;

	bool bInteracting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bIsBackpackOpen;

	UFUNCTION(BlueprintCallable)
	void OpenPauseMenu();
	UFUNCTION(BlueprintCallable)
	void ClosePauseMenu();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void PlayAnimation();
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void PlayReverseAnimation();
	
	void ChangeEsc();
	bool bEscDown;

	void Turn(float Value);
	bool bShouldTurnRotate;

	void LookUp(float Value);
	bool bShouldLookUpRotate;

	bool bShouldRollRotate;

	void SetBackgroundBlur();
	UFUNCTION(BlueprintCallable)
	void ShowInspectionHUD();
	void HideInspectionHUD();

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame();
	void LoadGameNoSwitch();

	void CheckIfSaved();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boolean")
	bool bIsGameSaved;
	bool bNewGame;

	void CloseBackpack();
	UFUNCTION(BlueprintCallable)
	void RemoveFromBackpack();
	void DeleteBackgroundBlur();
	void PickupItemToBackpack();
	void EquipFlashlight();
	void EquipBackpack();
	void PickupItem(class  AInventoryItem* Item);
	void SwitchLevel(FName LevelName);
	void StaminaBarLogic(float DeltaStamina);
	void SetMovementStatus(EMovementStatus Status);
	void SetEquippedFlashlight(AFlashlight* FlashlightToSet);
	void SetEquippedBackpack(ABackpack* BackpackToSet);

	FORCEINLINE AFlashlight* GetEquippedFlashlight() { return EquippedFlashlight; }
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class AItem* GetActiveOverlappingItem() const { return ActiveOverlappingItem; }
	FORCEINLINE class ALeverCollisionBox* GetActiveOverlappingCollision() const { return ActiveOverlappingCollision; }
	FORCEINLINE FString GetKeypadCode() { return KeypadCode; }

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* ItemToSet) { ActiveOverlappingItem = ItemToSet; }
	FORCEINLINE void SetActiveOverlappingCollision(ALeverCollisionBox* CollisionToSet) { ActiveOverlappingCollision = CollisionToSet; }
	FORCEINLINE void SetbBClicked(bool ToThis) { bBClicked = ToThis; }
	FORCEINLINE void SetKeypadCode(FString ToThis) { KeypadCode = ToThis; }
	FORCEINLINE void AppendKeypadCode(FString ToThis) { KeypadCode.Append(ToThis); }
	FORCEINLINE void SetObjectToRotate(UStaticMeshComponent* ToThis) { ItemToRotate = ToThis; }
	FORCEINLINE void SetObjectToMove(UStaticMeshComponent* ToThis) { ItemToMove = ToThis; }
};