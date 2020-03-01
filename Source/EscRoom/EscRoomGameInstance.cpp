// Fill out your copyright notice in the Description page of Project Settings.


#include "EscRoomGameInstance.h"

UEscRoomGameInstance::UEscRoomGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bNewGame = true;
	bShowed = false;
	MusicVolume = 1.1f;
}