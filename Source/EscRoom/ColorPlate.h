// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorPlate.generated.h"

UCLASS()
class ESCROOM_API AColorPlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorPlate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* PlateCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
	class AStaticMeshActor* ConnectorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class AColorBall* ColorBall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material")
	UMaterialInterface* ConnectorMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ColorBall")
	class AColorBall* OverlappedBall;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CheckPlateCollision();

	bool bCheckMaterial;
	bool bRevertMaterial;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);
};
