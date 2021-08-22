// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/WidgetComponent.h"

#include "Asteroid.generated.h"

UCLASS()
class ASTEROIDSINVADERS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid Properties")
	float VelocityMin = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid Properties")
	float VelocityMax = 10.f;
	UPROPERTY(EditAnywhere, Category = "Asteroid Properties")
	UStaticMeshComponent *AsteroidMesh;
	UPROPERTY(EditAnywhere, Category = "Asteroid Properties")
	float MinScale = 0.5;
	UPROPERTY(EditAnywhere, Category = "Asteroid Properties")
	float MaxScale = 1.5;
	UPROPERTY(EditAnywhere, Category = "Asteroid Properties")
	UParticleSystem *ExplosionSparks;
	UPROPERTY(EditAnywhere, Category = "Asteroid Properties")
	USoundBase *ExplosionSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Asteroid Properties")
	int PointsForDestroy = 100;

// Class Variables
private:
	float InitialVelocity;
	FTimerHandle AsteroidLifeTimer;
	FVector MoveVector;
	UPROPERTY(EditDefaultsOnly, Category = "Asteroid Properties")
	float AsteroidLifetime = 2.f;

	//Random Asteroid rotation values
	float Pitch;
	float Yaw;
	float Roll;

	//Destroy actions 
	FTimerHandle AfterDestroyTimer;
	UPROPERTY(EditDefaultsOnly, Category = "Asteroid Properties")
	float AfterLifetime = 0.5f;

//CLASS CONSTANTS
private:
	//Random rotation vector scale range
	const float CT_MaxRotationSpeed =  2.f;
	const float CT_MinRotationSpeed = -2.f;
	//Asteroid Mesh properties
	const FName CT_AsteroidMeshName = (TEXT("AsteroidMesh"));

//PUBLIC METHODS
public:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
                      	AActor* OtherActor, 
                     	UPrimitiveComponent* OtherComp, 
                      	int32 OtherBodyIndex, 
                      	bool bFromSweep, 
                      	const FHitResult &SweepResult );

	void DestroyAsteroidHandle();

	void DeleteAsteroid();

	//Event for Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "AsteroidsEvents")
	void DestroyAsteroid();
};
