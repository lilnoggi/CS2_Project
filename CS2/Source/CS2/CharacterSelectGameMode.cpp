// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectGameMode.h"

#include "MascotPlayerController.h"
#include "Engine/TargetPoint.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

ACharacterSelectGameMode::ACharacterSelectGameMode()
{
	// Initialise the array with 4 'false' values (all mascots are free)
	LockedMascots.Init(false, 4);
}

void ACharacterSelectGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Hardware delay
	FTimerHandle HardwareDelayTimer;
	GetWorldTimerManager().SetTimer(HardwareDelayTimer, this, &ACharacterSelectGameMode::InitialiseLevel, 0.5f, false);
}

void ACharacterSelectGameMode::InitialiseLevel()
{
	// Create local players for controllers 1, 2, and 3 (0 is already created)
	for (int32 i = 1; i < 4; i++)
	{
		if (!UGameplayStatics::GetPlayerController(GetWorld(), i))
		{
			UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
		}
	}
	
	// Find the target points in the booths
	TArray<AActor*> TargetPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TargetPoints);
	
	// Spawn 4 default Pandas, possess them, and save the booth locations
	for (int32 i = 0; i < 4; i++)
	{
		if (TargetPoints.IsValidIndex(i))
		{
			FTransform SpawnTransform = TargetPoints[i]->GetActorTransform();
			BoothSpawnLocations.Add(SpawnTransform);
			
			if (DefaultMascotClass)
			{
				APawn* SpawnedMascot = GetWorld()->SpawnActor<APawn>(DefaultMascotClass, SpawnTransform);
				APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), i);
				if (PC && SpawnedMascot)
				{
					PC->Possess(SpawnedMascot);
				}
			}
		}
	}
	
	// Draw the main HUD UI
	OnInitialiseHUD();
}

void ACharacterSelectGameMode::RequestPlayerJoin(APlayerController* CallingController)
{
	if (!CallingController)
	{
		return;
	}
	
	// Check if this controller has already joined
	if (!JoinedControllers.Contains(CallingController))
	{
		// Add them to the array and get their player number
		int32 PlayerIndex = JoinedControllers.Add(CallingController);
		
		// Trigger the Blueprint to draw the personal UI overlay
		OnPlayerJoinedUI(CallingController, PlayerIndex);
	}
}

bool ACharacterSelectGameMode::TryLockMascot(EMascot RequestedMascot)
{
	// Convert the Enum to an Int
	int32 Index = static_cast<int32>(RequestedMascot);
	
	// Check if the index is valid and if the mascot is NOT locked
	if (LockedMascots.IsValidIndex(Index) && !LockedMascots[Index])
	{
		// Lock the mascot so no one can take it
		LockedMascots[Index] = true;
		return true; // Succeed
	}
	
	// If locked, fail
	return false;
}

void ACharacterSelectGameMode::UnlockMascot(EMascot MascotToUnlock)
{
	int32 Index = static_cast<int32>(MascotToUnlock);
	
	if (LockedMascots.IsValidIndex(Index))
	{
		// Make the mascot available again
		LockedMascots[Index] = false;
	}
}

bool ACharacterSelectGameMode::AreAllPlayersReady()
{
	// Ensure at least 1 player has joined before allowing the game to start
	if (JoinedControllers.Num() == 0)
	{
		return false;
	}
	
	// Loop through every player who has pressed join
	for (APlayerController* PC : JoinedControllers)
	{
		AMascotPlayerController* MascotPC = Cast<AMascotPlayerController>(PC);
		
		// If there is at least one player that is not ready, return false
		if (MascotPC && !MascotPC->bIsReady)
		{
			return false;
		}
	}
	
	// If the loop ends without finding anyone unready, everyone is ready!
	return true;
}


