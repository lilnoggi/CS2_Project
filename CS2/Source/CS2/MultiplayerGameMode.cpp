// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "TimerManager.h"

void AMultiplayerGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Wait 0.5s to let hardware initialise, then call InitialiseLevel
	FTimerHandle HardwareDelayTimer;
	GetWorldTimerManager().SetTimer(HardwareDelayTimer, this, &AMultiplayerGameMode::InitialiseLevel, 0.5f, false);
}

void AMultiplayerGameMode::InitialiseLevel()
{
	// Spawn Player Actors based on Game Instance choices
	UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
	if (GI)
	{
		for (int32 i = 0; i < GI->PlayerRoster.Num(); i++)
		{
			// Check if the player has joined, and ensure a valid spawn point is available
			if (GI->PlayerRoster[i].bHasJoined && LobbySpawnLocations.IsValidIndex(i))
			{
				int32 MascotIndex = static_cast<int32>(GI->PlayerRoster[i].SelectedMascot);
				
				// Ensure MascotClasses array has blueprints
				if (MascotClasses.IsValidIndex(MascotIndex) && MascotClasses[MascotIndex] != nullptr)
				{
					// Get from the ordered array
					FTransform SpawnTransform = LobbySpawnLocations[i];
					APawn* SpawnedMascot = GetWorld()->SpawnActor<APawn>(MascotClasses[MascotIndex], SpawnTransform);
					
					// Get the specific PlayerController and Possess the character
					APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), i);
					if (PC && SpawnedMascot)
					{
						PC->Possess(SpawnedMascot);
					}
				}
			}
		}
	}
	
	// Initialise the HUD
	OnInitialiseHUD();
}

void AMultiplayerGameMode::RequestPlayerJoinLate(APlayerController* CallingController, FTransform SpawnTransform)
{
	if (!CallingController)
	{
		return;
	}
	
	/*
	// Check if JoinedControllers contains the controller
	if (JoinedControllers.Contains(CallingController))
	{
		return;
	}
	
	// Add to the array and save the player's slot
	int32 PlayerIndex = JoinedControllers.Add(CallingController);
	*/
	
	// Get the true hardware ID 
	int32 PlayerIndex = UGameplayStatics::GetPlayerControllerID(CallingController);
	
	UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
	if (GI)
	{
		// Create an array of all available mascots
		TArray<EMascot> AvailableMascots = { EMascot::Panda, EMascot::Skunk, EMascot::Wolf, EMascot::Cat };
		
		// Loop through the Roster and remove mascots that are already taken
		for (const FPlayerData& PlayerData : GI->PlayerRoster)
		{
			if (PlayerData.bHasJoined)
			{
				AvailableMascots.Remove(PlayerData.SelectedMascot);
			}
		}
		
		// Pick a random remaining mascot
		if (AvailableMascots.Num() > 0)
		{
			int32 RandIndex = FMath::RandRange(0, AvailableMascots.Num() - 1);
			EMascot AssignedMascot = AvailableMascots[RandIndex];
			
			// Save data to Game Instance
			if (GI->PlayerRoster.IsValidIndex(PlayerIndex))
			{
				GI->PlayerRoster[PlayerIndex].bHasJoined = true;
				GI->PlayerRoster[PlayerIndex].SelectedMascot = AssignedMascot;
			}
			
			// Spawn the Actor and Possess
			int32 MascotInt = static_cast<int32>(AssignedMascot);
			if (MascotClasses.IsValidIndex(MascotInt) && MascotClasses[MascotInt] != nullptr)
			{
				APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(MascotClasses[MascotInt], SpawnTransform);
				if (SpawnedPawn)
				{
					CallingController->Possess(SpawnedPawn);
				}
			}
		}
	}
	
	// Call the Blueprint Event so the specific map can update its UI
	OnPlayerJoinedLateUI(CallingController, PlayerIndex);
}
