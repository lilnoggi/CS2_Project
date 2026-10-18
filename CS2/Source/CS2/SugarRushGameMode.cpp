// Fill out your copyright notice in the Description page of Project Settings.


#include "SugarRushGameMode.h"
#include "MascotGameInstance.h"
#include "Kismet/GameplayStatics.h"


void ASugarRushGameMode::CheckWinCondition(int32 PlayerIndex)
{
	UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
	
	// Ensure the Game Instance and the player's data slot exist
	if (GI && GI->PlayerRoster.IsValidIndex(PlayerIndex))
	{
		// Check if they hit the jar's capacity
		if (GI->PlayerRoster[PlayerIndex].MiniGameScore >= 100)
		{
			// Trigger the Blueprint event to display the winner
			OnPlayerWon(PlayerIndex);
		}
	}
}
