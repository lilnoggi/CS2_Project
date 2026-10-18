// Fill out your copyright notice in the Description page of Project Settings.


#include "CandySpawner.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ACandySpawner::ACandySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Drops a new burst every 5 seconds
	RespawnDelay = 5.0f;
	
	// Drops 3 candies at a time
	BurstCount = 3;

}

// Called when the game starts or when spawned
void ACandySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Start a repeating timer that fires the SpawnBurst function continously
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ACandySpawner::SpawnBurst, RespawnDelay, true);
	
	// Spawn the first burst when the match starts
	SpawnBurst();
	
}

void ACandySpawner::SpawnBurst()
{
	// Ensure there is a valid candy blueprint selected
	if (CandyClass && GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		// Loop exactly 'BurstCount' times
		for (int32 i = 0; i < BurstCount; i++)
		{
			// Generate a random horizontal offset between -100 and 100 units
			FVector RandomOffset = FVector(FMath::RandRange(-500.0f, 500.0f), FMath::RandRange(-500.0f, 500.0f), 0.0f);
			FVector SpawnLocation = GetActorLocation() + RandomOffset;
			
			// Spawn the candy at the scattered location
			GetWorld()->SpawnActor<AActor>(CandyClass, SpawnLocation, GetActorRotation(), SpawnParams);
		}
	}
}

