// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Asteroid.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(CT_BulletMeshName);
	BulletMesh->AddLocalRotation(CT_BulletMeshHorizontalPosition, false);
	RootComponent = BulletMesh;

	BulletMesh->OnComponentBeginOverlap.AddDynamic(this,&ABullet::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// ForwardVector = this->GetActorForwardVector();
	GetWorldTimerManager().SetTimer(ShootingLifeTimer, this, &ABullet::DeleteBullet, BulletLifetime);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(CT_WorldForwardVector*BulletSpeed*GetWorld()->DeltaTimeSeconds,true);
}

void ABullet::DeleteBullet() 
{
	this->Destroy();
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
						  	 AActor* OtherActor, 
						 	 UPrimitiveComponent* OtherComp, 
						  	 int32 OtherBodyIndex, 
						  	 bool bFromSweep, 
						  	 const FHitResult &SweepResult) 
{
	UE_LOG(LogTemp, Warning, TEXT("Bullet Begin Overlap %s"), *OtherActor->GetName());
	AAsteroid *OverlappedAsteroid = Cast<AAsteroid>(OtherActor);
	if(OverlappedAsteroid != nullptr){
		this->DeleteBullet();
		OverlappedAsteroid->DestroyAsteroidHandle();
	}
}

