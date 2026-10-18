// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoringZone.h"
#include "MascotGameInstance.h"
#include "SugarRushGameMode.h"
#include "SugarRushGameMode.h"

// Sets default values
AScoringZone::AScoringZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ZoneCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneCollision"));
	RootComponent = ZoneCollision;
	
	ZoneCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void AScoringZone::AwardPointsAndDestroyCandy(int32 PointsToAdd, AActor* CandyToDestroy)
{
	UMascotGameInstance* GI = Cast<UMascotGameInstance>(GetGameInstance());
	if (GI && GI->PlayerRoster.IsValidIndex(ZoneOwnerIndex))
	{
		// Add the score directly to the struct in memory
		GI->PlayerRoster[ZoneOwnerIndex].MiniGameScore += PointsToAdd;
		
		// Ask the Game Mode to check if this specific point triggers a win
		ASugarRushGameMode* SRGameMode = Cast<ASugarRushGameMode>(GetWorld()->GetAuthGameMode());
		if (SRGameMode)
		{
			SRGameMode->CheckWinCondition(ZoneOwnerIndex);
		}
	}
	
	if (CandyToDestroy)
	{
		CandyToDestroy->Destroy();
	}
}

// Called when the game starts or when spawned
void AScoringZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoringZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

