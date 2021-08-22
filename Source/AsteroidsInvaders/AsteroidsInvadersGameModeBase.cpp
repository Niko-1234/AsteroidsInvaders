// Copyright Epic Games, Inc. All Rights Reserved.


#include "AsteroidsInvadersGameModeBase.h"
#include "EngineUtils.h"
#include "TimerManager.h"

AAsteroidsInvadersGameModeBase::AAsteroidsInvadersGameModeBase() 
{
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
}

void AAsteroidsInvadersGameModeBase::BeginPlay() 
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Game has started"));

    for (ASpawner *Spawner : TActorRange<ASpawner>(GetWorld())){
        UE_LOG(LogTemp, Warning, TEXT("Spawner Getted"));
        Spawners.Add(Spawner);
    }

    if(Spawners.Num() == 0){
        UE_LOG(LogTemp, Warning, TEXT("There are no spawners on map"));
    }
    
    SpawnPossible = true;
    SpawnIncrementationPossible = true;
}

void AAsteroidsInvadersGameModeBase::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);

    //Spawning 
    if (SpawnPossible && Spawners.Num() > 0){
		SpawnAsteroidsBySpawners();
    }

    //Spawning Increment
    if(SpawnIncrementationPossible){
		SpawningFrequencyIncrement();
    }
    
}

void AAsteroidsInvadersGameModeBase::SpawnAsteroidsBySpawners()
{
	int RandSpawnerID = FMath::RandRange(0, (Spawners.Num() - 1));
	SpawnPossible = false;
	float SpawnDelay = 1.f / AppearanceFrequency;
	ASpawner* TempSpawner = Spawners[RandSpawnerID];
	TempSpawner->SpawnAsteroid();
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AAsteroidsInvadersGameModeBase::SpawningOn, SpawnDelay);
}

void AAsteroidsInvadersGameModeBase::SpawningFrequencyIncrement()
{
	float SpawnIncDelay = 1.f / AppearanceFrequencyIncrease;
	AppearanceFrequency++;
	SpawnIncrementationPossible = false;
	GetWorldTimerManager().SetTimer(SpawnIncrementationTimer, this, &AAsteroidsInvadersGameModeBase::IncrementOn, SpawnIncDelay);
}

void AAsteroidsInvadersGameModeBase::SpawningOn() 
{
    SpawnPossible = true;
}

void AAsteroidsInvadersGameModeBase::IncrementOn() 
{
    SpawnIncrementationPossible = true;   
}

int AAsteroidsInvadersGameModeBase::GetTotalScore() 
{
    return TotalScore;
}

void AAsteroidsInvadersGameModeBase::AddPointsToTotalScore(int Points) 
{
    TotalScore += Points;
}

