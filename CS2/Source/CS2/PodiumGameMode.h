// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGameMode.h"
#include "PodiumGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CS2_API APodiumGameMode : public AMultiplayerGameMode
{
	GENERATED_BODY()
	
public:
	// Overrides the standard lobby spawning to spawn players based on rank
	virtual void InitialiseLevel() override;
};
