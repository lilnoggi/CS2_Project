// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CandySpawner.generated.h"

UCLASS()
class CS2_API ACandySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// The specific blueprint candy to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> CandyClass;
	
	// How many seconds between each candy burst
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float RespawnDelay;
	
	// How many candies shoot out during a single burst
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 BurstCount;
	
	// TODO: Add randomiser for how many candies drop
	
private:
	FTimerHandle RespawnTimerHandle;
	
	// --------------------------------------------------------------------
	
	UFUNCTION()
	void SpawnBurst();
};
