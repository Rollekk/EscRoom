// Fill out your copyright notice in the Description page of Project Settings.


#include "JohnyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter.h"

void UJohnyAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Char = Cast<AMainCharacter>(Pawn);
		}
	}

}

void UJohnyAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
		bIsCrouching = Char->bIsCrouched;

		if (Char == nullptr)
		{
			Char = Cast<AMainCharacter>(Pawn);
		}

	}
}
