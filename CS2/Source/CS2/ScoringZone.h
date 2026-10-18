// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ScoringZone.generated.h"

UCLASS()
class CS2_API AScoringZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoringZone();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* ZoneCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	int32 ZoneOwnerIndex;
	
	UFUNCTION(BlueprintCallable, Category = "Scoring")
	void AwardPointsAndDestroyCandy(int32 PointsToAdd, AActor* CandyToDestroy);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
