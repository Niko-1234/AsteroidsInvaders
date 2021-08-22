// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class ASTEROIDSINVADERS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// PROPERTIES
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Properties")
	float BulletSpeed = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties")
	float BulletLifetime = 2.f;
	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
	UStaticMeshComponent *BulletMesh;

// PRIVATE VARIABLES
private: 
	FTimerHandle ShootingLifeTimer;
	FVector ForwardVector;

// CLASS CONSTANTS
private:
	const FName CT_BulletMeshName = (TEXT("BulletMesh"));
	const FVector CT_WorldForwardVector = FVector(1,0,0);
	const FQuat CT_BulletMeshHorizontalPosition = FQuat(FRotator(90, 0, 0));

// PRIVATE METHODS
private:
	void DeleteBullet();

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
                      	AActor* OtherActor, 
                     	UPrimitiveComponent* OtherComp, 
                      	int32 OtherBodyIndex, 
                      	bool bFromSweep, 
                      	const FHitResult &SweepResult );
};
