// Fill out your copyright notice in the Description page of Project Settings.


#include "MascotPlayerController.h"
#include "CharacterSelectGameMode.h"
#include "MascotGameInstance.h"
#include "MultiplayerGameMode.h"
#include "Kismet/GameplayStatics.h"

AMascotPlayerController::AMascotPlayerController()
{
	HoveredIndex = 0;
	bIsReady = false;
	bHasJoinedLobby = false;
	CurrentDisplayCharacter = nullptr;
}

void AMascotPlayerController::HandleJoinInput()
{
	AGameModeBase* CurrentGM = GetWorld()->GetAuthGameMode();
	
	// SCENARIO 1: Character Selection Map
	if (ACharacterSelectGameMode* CSGameMode = Cast<ACharacterSelectGameMode>(CurrentGM))
	{
		if (!bHasJoinedLobby)
		{
			// First time pressing join
			CSGameMode->RequestPlayerJoin(this);
			bHasJoinedLobby = true;
			OnJoinedCharacterSelectUI(); // Hide Press Start
		}
		else if (!bIsReady)
		{
			// Already joined, so pressing joins means select
			if (SelectCharacter())
			{
				OnCharacterSelectedUI(); // Tell blueprint to turn text to "READY!"
			}
		}
		else
		{
			// Already selected, pressing join again tries to start the level
			OnStartGame();
		}
	}
	// Scenario 2: In Lobby or Mini-Game
	else if (AMultiplayerGameMode* MPGameMode = Cast<AMultiplayerGameMode>(CurrentGM))
	{
		UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
		int32 PlayerID = UGameplayStatics::GetPlayerControllerID(this);
		
		if (GI && GI->PlayerRoster.IsValidIndex(PlayerID))
		{
			// Only trigger a late-joiner if they have not joined yet
			if (!GI->PlayerRoster[PlayerID].bHasJoined)
			{
				// Get the exact spawn location for their specific player slot
				FTransform SpawnTransform = FTransform::Identity;
				if (MPGameMode->LobbySpawnLocations.IsValidIndex(PlayerID))
				{
					SpawnTransform = MPGameMode->LobbySpawnLocations[PlayerID];
				}
				
				MPGameMode->RequestPlayerJoinLate(this, SpawnTransform);
			}
		}
	}
}

void AMascotPlayerController::CycleMascot(int32 Direction)
{
	// Do nothing if already chosen
	if (bIsReady)
	{
		return;
	}
	
	HoveredIndex += Direction;
	
	// Handle array
	if (HoveredIndex > 3)
	{
		HoveredIndex = 0;
	}
	
	if (HoveredIndex < 0)
	{
		HoveredIndex = 3;
	}
}

bool AMascotPlayerController::SelectCharacter()
{
	if (bIsReady)
	{
		return true;
	}
	
	// Get the Game Mode
	ACharacterSelectGameMode* GM = Cast<ACharacterSelectGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		// Check if this mascot can be selected / unlocked
		EMascot DesiredMascot = static_cast<EMascot>(HoveredIndex);
		bool bSuccessfullySelected = GM->TryLockMascot(DesiredMascot);
		
		if (bSuccessfullySelected)
		{
			bIsReady = true;
			
			// Save the choice to the Game Instance
			UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
			if (GI)
			{
				int32 PlayerID = UGameplayStatics::GetPlayerControllerID(this);
				if (GI->PlayerRoster.IsValidIndex(PlayerID))
				{
					GI->PlayerRoster[PlayerID].SelectedMascot = DesiredMascot;
					GI->PlayerRoster[PlayerID].bHasJoined = true;
				}
			}
			
			// Character successfully chosen
			return true;
		}
		else
		{
			// TODO: Play error sound here
			UE_LOG(LogTemp, Warning, TEXT("Character is already taken!"));
		}
	}
	
	// Failed to select (either aleady selected or GameMode cast failed)
	return false;
}

void AMascotPlayerController::CancelSelection()
{
	if (!bIsReady)
	{
		return;
	}
	
	// Game Mode make the character available again
	ACharacterSelectGameMode* GM = Cast<ACharacterSelectGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		EMascot CurrentMascot = static_cast<EMascot>(HoveredIndex);
		GM->UnlockMascot(CurrentMascot);
	}
	
	// Update local state and clear from Game Instance
	bIsReady = false;
	
	UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
	if (GI)
	{
		int32 PlayerID = UGameplayStatics::GetPlayerControllerID(this);
		if (GI->PlayerRoster.IsValidIndex(PlayerID))
		{
			GI->PlayerRoster[PlayerID].bHasJoined = false;
		}
	}
}
