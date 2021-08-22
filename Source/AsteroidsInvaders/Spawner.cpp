// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnAsteroid() 
{

	//GetRandom Asteroid Type
	int AsteroidType = FMath::RandRange(0,(AsteroidsTypes.Num() - 1));

	//Set Asteroid spawn loaction and rotation
	FVector AsteroidSpawnLocation = this->GetActorLocation();
	FRotator AsteroidSpawnRotation = this->GetActorRotation();

	//Spawn Actor
	Asteroid = GetWorld()->SpawnActor<AAsteroid>(AsteroidsTypes[AsteroidType],AsteroidSpawnLocation,AsteroidSpawnRotation);
	if(Asteroid == nullptr){
		UE_LOG(LogTemp, Warning, TEXT("No AsteroidClass%i class defined"), AsteroidType);
	}
}

