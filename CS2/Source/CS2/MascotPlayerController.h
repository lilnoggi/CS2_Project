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
	
	// -----------------------------------------------------------------------
	
	// Called from Enhanced Input D-Pad (1 for Right, -1 for Left)
	UFUNCTION(BlueprintCallable, Category = "Selection")
	void CycleMascot(int32 Direction);
	
	// Called from Select Enhanced Input Action
	UFUNCTION(BlueprintCallable, Category = "Selection")
	bool LockInSelection();
	
	// Called from Cancel Enhanced Input Action
	UFUNCTION(BlueprintCallable, Category = "Selection")
	void CancelSelection();
};
