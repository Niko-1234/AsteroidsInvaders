// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Spawner.h"

#include "AsteroidsInvadersGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDSINVADERS_API AAsteroidsInvadersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAsteroidsInvadersGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

//PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AppearanceFrequency = 1.f; //How many asteroids shoud be spawned on the map per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AppearanceFrequencyIncrease= 1.f; //How many asteroids shoud be add to ApperenceFrequency per second

//Variables
private:
	UPROPERTY()
	TArray <ASpawner *> Spawners;

	// Spawn possibility indicator
	bool SpawnPossible = false;
	FTimerHandle SpawnTimer;

	// Spawn incrementation possibility indicator
	bool SpawnIncrementationPossible = false;
	FTimerHandle SpawnIncrementationTimer;

	int TotalScore;

//PRIVATE METHODS
private:
	void SpawnAsteroidsBySpawners();
	void SpawningFrequencyIncrement();
	void SpawningOn();
	void IncrementOn();

public:
	UFUNCTION(BlueprintCallable)
	int GetTotalScore();
	void AddPointsToTotalScore(int Points);
};
