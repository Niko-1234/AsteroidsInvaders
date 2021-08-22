// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Asteroid.h"

#include "Spawner.generated.h"

UCLASS()
class ASTEROIDSINVADERS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// PROPERTIES
public:
	UPROPERTY(EditDefaultsOnly)
	TArray< TSubclassOf<AAsteroid>> AsteroidsTypes;

private:
	UPROPERTY()
	AAsteroid *Asteroid;

public:
	void SpawnAsteroid();

};
