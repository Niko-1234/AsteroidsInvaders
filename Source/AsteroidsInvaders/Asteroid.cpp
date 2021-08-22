// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Spaceship.h"
#include "Kismet/GameplayStatics.h"
#include "AsteroidsInvadersGameModeBase.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(CT_AsteroidMeshName);
	RootComponent = AsteroidMesh;

	AsteroidMesh->OnComponentBeginOverlap.AddDynamic(this,&AAsteroid::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	InitialVelocity = FMath::RandRange(VelocityMin,VelocityMax);
	MoveVector = GetActorForwardVector();
	GetWorldTimerManager().SetTimer(AsteroidLifeTimer, this, &AAsteroid::DeleteAsteroid, AsteroidLifetime);
	
	Pitch = FMath::RandRange(CT_MinRotationSpeed, CT_MaxRotationSpeed);
	Yaw = FMath::RandRange(CT_MinRotationSpeed, CT_MaxRotationSpeed);
	Roll = FMath::RandRange(CT_MinRotationSpeed, CT_MaxRotationSpeed);

	float AsteroidSize = FMath::RandRange(MinScale,MaxScale);
	AsteroidMesh->SetWorldScale3D(FVector(AsteroidSize,AsteroidSize,AsteroidSize));
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	AddActorWorldOffset(MoveVector*InitialVelocity*GetWorld()->DeltaTimeSeconds,true);

	//Asteroid random space rotation
	FRotator Rotation = FRotator(Pitch,Yaw,Roll);
	AddActorLocalRotation(FQuat(Rotation),true);

}

void AAsteroid::DeleteAsteroid() 
{
	Destroy();
}

void AAsteroid::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
                      	AActor* OtherActor, 
                     	UPrimitiveComponent* OtherComp, 
                      	int32 OtherBodyIndex, 
                      	bool bFromSweep, 
                      	const FHitResult &SweepResult )
{

	UE_LOG(LogTemp, Warning, TEXT("Asteroid Begin Overlap %s"), *OtherActor->GetName());
	ASpaceship *OverlappedShip = Cast<ASpaceship>(OtherActor);
	if (OverlappedShip != nullptr){
		OverlappedShip->DestroyShip();
	}
}

void AAsteroid::DestroyAsteroidHandle() 
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplosionSparks,this->GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ExplosionSound,this->GetActorLocation());
	this->SetActorEnableCollision(false);
	AsteroidMesh->SetVisibility(false);
	DestroyAsteroid();//Event for blueprint
	
	AAsteroidsInvadersGameModeBase *SpaceshipGameMode = Cast<AAsteroidsInvadersGameModeBase>(GetWorld()->GetAuthGameMode());
	if(SpaceshipGameMode != nullptr)
		SpaceshipGameMode->AddPointsToTotalScore(PointsForDestroy);
	else
		UE_LOG(LogTemp, Warning, TEXT("Wrong Game mode"));

	GetWorldTimerManager().SetTimer(AfterDestroyTimer, this, &AAsteroid::DeleteAsteroid, AfterLifetime);
}

