// Fill out your copyright notice in the Description page of Project Settings.


#include "SugarRushGameMode.h"
#include "MascotGameInstance.h"


void ASugarRushGameMode::CheckWinCondition(int32 PlayerIndex)
{
	UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
	
	// Ensure the Game Instance and the player's data slot exist
	if (GI && GI->PlayerRoster.IsValidIndex(PlayerIndex))
	{
		// Check if they hit the jar's capacity
		if (GI->PlayerRoster[PlayerIndex].MiniGameScore >= 100)
		{
			// Award 5 victory points for winning this mini game
			// Call the base class EndMatch function (MultiplayerGameMode)
			EndMatch(PlayerIndex, 5);
		}
	}
}
