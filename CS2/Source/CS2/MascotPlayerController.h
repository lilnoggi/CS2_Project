// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MascotGameInstance.h" // Needed for the EMascot
#include "MascotPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CS2_API AMascotPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
	AMascotPlayerController();
	
	// Tracks which character is being looked at currently
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Selection")
	int32 HoveredIndex;
	
	// Returns True if the player has selected their Mascot
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Selection")
	bool bIsReady;
	
	// Holds the 3D actor spawned in the booth
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Selection")
	AActor* CurrentDisplayCharacter;
	
	// A list of blueprints to spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selection")
	TArray<TSubclassOf<AActor>> MascotClasses;
	
	// Tracks if the player has pressed start to join the Character Select screen
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Selection")
	bool bHasJoinedLobby;
	
	// -----------------------------------------------------------------------
	
	// Function to handle all Join/Lock/LateJoin logic
	UFUNCTION(BlueprintCallable, Category = "Input")
	void HandleJoinInput();
	
	// Called from Enhanced Input D-Pad (1 for Right, -1 for Left)
	UFUNCTION(BlueprintCallable, Category = "Input|Selection")
	void CycleMascot(int32 Direction);
	
	// Called from Select Enhanced Input Action
	UFUNCTION(BlueprintCallable, Category = "Input|Selection")
	bool SelectCharacter();
	
	// Called from Cancel Enhanced Input Action
	UFUNCTION(BlueprintCallable, Category = "Input|Selection")
	void CancelSelection();
	
	// Triggers when the player joins Character Select screen for the first time
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnJoinedCharacterSelectUI();
	
	// Triggers when a player successfully selects their character
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnCharacterSelectedUI();
	
	// Triggers the Start Game logic
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnStartGame();
};
