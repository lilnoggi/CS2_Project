// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MascotGameInstance.h"
#include "CharacterSelectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CS2_API ACharacterSelectGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACharacterSelectGameMode();
	virtual void BeginPlay() override;
	
	// Track who has pushed Start to join
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Roster")
	TArray<APlayerController*> JoinedControllers;
	
	// Default placeholder to spawn before the player selects anything (Panda)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<APawn> DefaultMascotClass;
	
	// An array of the spawn locations in the display booths
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<FTransform> BoothSpawnLocations;
	
	// An array to track which mascots are taken (index 0=Panda, 1=Skunk, 2=Wolf, 3=Cat)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roster")
	TArray<bool> LockedMascots;
	
	// -----------------------------------------------------------------------------------
	
	void InitialiseLevel();
	
	// Called by the Player Controller when a player presses the Join Input Button
	UFUNCTION(BlueprintCallable, Category = "Roster")
	bool TryLockMascot(EMascot RequestedMascot);
	
	// Called by the Player Controller when a player pushes the Cancel Input Button
	UFUNCTION(BlueprintCallable, Category = "Roster")
	void UnlockMascot(EMascot MascotToUnlock);
	
	// Request Join Function
	UFUNCTION(BlueprintCallable, Category = "Roster")
	void RequestPlayerJoin(APlayerController* CallingController);
	
	// Check for everyone has a character selected
	UFUNCTION(BlueprintCallable, Category = "Level")
	bool AreAllPlayersReady();
	
	// Blueprint Event for UI drawing
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnInitialiseHUD();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnPlayerJoinedUI(APlayerController* CallingController, int32 PlayerIndex);
};
