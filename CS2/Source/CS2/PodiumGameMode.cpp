// Fill out your copyright notice in the Description page of Project Settings.


#include "PodiumGameMode.h"
#include "MascotGameInstance.h"
#include "Kismet/GameplayStatics.h"

// A temporary struct to help sort scores
struct FPlayerRank
{
	int32 PlayerIndex;
	int32 Score;
	
	// Sort from highest to lowest
	bool operator<(const FPlayerRank& Other) const
	{
		return Score > Other.Score;
	}
};

void APodiumGameMode::InitialiseLevel()
{
	UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
	if (!GI)
	{
		return;
	}
	
	// Gather all active players and their scores
	TArray<FPlayerRank> Ranks;
	for (int32 i = 0; i < GI->PlayerRoster.Num(); i++)
	{
		if (GI->PlayerRoster[i].bHasJoined)
		{
			FPlayerRank NewRank;
			NewRank.PlayerIndex = i;
			NewRank.Score = GI->PlayerRoster[i].TotalScore;
			Ranks.Add(NewRank);
		}
	}
	
	// Sort the array (1st place Ranks[0], 2nd Ranks[1]...)
	Ranks.Sort();
	
	// Spawn players on the podiums in order
	for (int32 RankIndex = 0; RankIndex < Ranks.Num(); RankIndex++)
	{
		int32 TruePlayerIndex = Ranks[RankIndex].PlayerIndex;
		int32 MascotIndex = static_cast<int32>(GI->PlayerRoster[TruePlayerIndex].SelectedMascot);
		
		// Ensure there is a valid spawn location and mascot class
		if (LobbySpawnLocations.IsValidIndex(RankIndex) && MascotClasses.IsValidIndex(MascotIndex) && MascotClasses[MascotIndex] != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			// RankIndex 0 spawns at LobbySpawnLocations[0]
			FTransform SpawnTransform = LobbySpawnLocations[RankIndex];
			APawn* SpawnedMascot = GetWorld()->SpawnActor<APawn>(MascotClasses[MascotIndex], SpawnTransform, SpawnParams);
			
			// Give the hardware controller back to the correct player
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), TruePlayerIndex);
			if (PC && SpawnedMascot)
			{
				PC->Possess(SpawnedMascot);
			}
		}
	}
	
	// Trigger blueprint to draw leaderboard UI
	OnInitialiseHUD();
}
