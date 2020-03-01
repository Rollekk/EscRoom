// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Symbol.generated.h"

UCLASS()
class ESCROOM_API ASymbol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASymbol();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	class ASymbolPuzzle* SymbolPuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* SymbolMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* ReleaseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundCue* PushSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float SoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Number")
	FString OrderNumber;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector OriginalLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsOn;

	void ChangeSymbol();

	UFUNCTION(BlueprintImplementableEvent, Category = "Mesh")
	void PushMesh();
	UFUNCTION(BlueprintImplementableEvent, Category = "Mesh")
	void ReleaseMesh();

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void UpdateMesh(float z);

	UFUNCTION()
	void OnPressedMouse(UPrimitiveComponent * TouchedComponent);

	FORCEINLINE void SetIsOn(bool ToThis) { bIsOn = ToThis; }
};
