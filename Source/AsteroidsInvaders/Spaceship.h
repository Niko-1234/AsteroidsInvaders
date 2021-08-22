// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Bullet.h"

#include "Spaceship.generated.h"

UCLASS()
class ASTEROIDSINVADERS_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship Properties")
	float HorizontalSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship Properties")
	float ShootingSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spaceship Properties")
	TSubclassOf<ABullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Spaceship Properties")
	float HorizontalRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Spaceship Properties")
	UParticleSystem *ExplosionSparks;

	UPROPERTY(EditAnywhere, Category = "Spaceship Properties")
	USoundBase *ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "Spaceship Properties")
	USoundBase *ShotSound;

	UPROPERTY(EditAnywhere, Category = "Spaceship Properties")
	USoundBase *EngineSound;

// PRIVATE VARIABLES
private: 

	FTimerHandle ShootingTimer;
	bool ShootingPossible;
	UPROPERTY()
	ABullet *Bullet;
	bool IsInPlayerInputRotation;
	FVector StartLocation;
	bool FloatingUp;
	float VerticalMove;

//CLASS CONSTANS
private:
	const float CT_ForwardAxisRotationBackSpeed = 0.5f; //Speed of raotation back movement
	const float CT_FloatingRange = 20.f;				//Range of up and down floating movement
	const float CT_FloatingSpeed = 1.f;					//Speed of up and down movement
	const FVector CT_WorldRightVector = FVector(0,1,0); //World orineted right vector
	const float CT_MaxForwardAxisRoatationAngle = 40.f; //Max rotation angle of spaceship in forward axis during movment
	const float CT_ForwardAxisRotationSpeed = 2.f;	    //Speed of spaceship rotation in forward axis during movment

// PRIVATE METHODS
private:
	void SidewaysMove(float AxisValue);
	void Shooting(float AxisValue);
	void ShootingOn();
	void StartMovement();
	void StopMovement();
	void SimulateFloating();
	void RotateToHorizontalIfPossible();
	void AddInputMoveRotation(float AxisValue);

// PUBLIC METHODS
public:
	void DestroyShip();
};
