// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGameMode.h"
#include "SugarRushGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CS2_API ASugarRushGameMode : public AMultiplayerGameMode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SugarRush")
	int32 TargetScore = 100;
	
	// ------------------------------------------------------------------
	
	// Checks if the specified player has hit the 100-point threshold
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void CheckWinCondition(int32 PlayerIndex);
};
