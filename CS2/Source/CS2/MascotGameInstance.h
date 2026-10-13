// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MascotGameInstance.generated.h"

// Mascot Types
UENUM(BlueprintType)
enum class EMascot : uint8
{
	Panda UMETA(DisplayName = "Panda"),
	Skunk UMETA(DisplayName = "Skunk"),
	Wolf UMETA(DisplayName = "Wolf"),
	Cat UMETA(DisplayName = "Cat"),
};

// Player Data
USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	bool bHasJoined = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	EMascot SelectedMascot = EMascot::Panda; // Default to Panda
	
	// TODO: Add other variables such as "int32 MiniGameScore = 0"
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
	// int32 MiniGameScore = 0;
};


/**
 * 
 */
UCLASS()
class CS2_API UMascotGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roster")
	TArray<FPlayerData> PlayerRoster;
	
	// The pool of remaining mini-games to choose from
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Progression")
	TArray<FName> MiniGamePool;
	
	// Override Init to size the array for 4 players automatically on startup
	virtual void Init() override;
	
};
