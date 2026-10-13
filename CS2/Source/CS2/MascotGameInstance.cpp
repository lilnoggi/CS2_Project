// Fill out your copyright notice in the Description page of Project Settings.


#include "MascotGameInstance.h"


void UMascotGameInstance::Init()
{
	Super::Init();
	
	// Create 4 empty player slots when the game begins
	PlayerRoster.SetNum(4);
}
