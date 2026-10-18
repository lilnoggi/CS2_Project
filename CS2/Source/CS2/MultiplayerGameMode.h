// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MascotGameInstance.h"
#include "MultiplayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CS2_API AMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	virtual void BeginPlay() override;
	
	// Track controllers that have successfully joined
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lobby")
	TArray<APlayerController*> JoinedControllers;
	
	// A list of mascot blueprints to spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TArray<TSubclassOf<APawn>> MascotClasses;
	
	// Manual spawn locations to prevent random Target Point shuffling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<FTransform> LobbySpawnLocations;
	
	// ----------------------------------------------------------------
	
	void InitialiseLevel();
	
	// Late-joiners function
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void RequestPlayerJoinLate(APlayerController* CallingController, FTransform SpawnTransform);
	
	// Function for drawing specific UI for this map
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnInitialiseHUD();
	
	// Update the map's specific UI
	UFUNCTION(BlueprintImplementableEvent, Category = "Lobby")
	void OnPlayerJoinedLateUI(APlayerController* Controller, int32 PlayerIndex);
	
	// Picks a random map from the Game Instance pool and loads it
	UFUNCTION(BlueprintCallable, Category = "Level Transition")
	void LoadNextMiniGame();
};
