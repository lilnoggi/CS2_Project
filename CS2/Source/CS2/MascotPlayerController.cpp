// Fill out your copyright notice in the Description page of Project Settings.


#include "MascotPlayerController.h"
#include "CharacterSelectGameMode.h"
#include "MascotGameInstance.h"
#include "Kismet/GameplayStatics.h"

AMascotPlayerController::AMascotPlayerController()
{
	HoveredIndex = 0;
	bIsReady = false;
	CurrentDisplayCharacter = nullptr;
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

bool AMascotPlayerController::LockInSelection()
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
