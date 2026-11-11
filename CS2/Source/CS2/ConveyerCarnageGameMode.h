// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGameMode.h"
#include "ConveyerCarnageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CS2_API AConveyerCarnageGameMode : public AMultiplayerGameMode
{
	GENERATED_BODY()

public:
	AConveyerCarnageGameMode();
	
protected:
	virtual void BeginPlay() override;
};
