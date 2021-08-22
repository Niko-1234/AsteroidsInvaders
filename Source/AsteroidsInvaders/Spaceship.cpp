// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"
#include "SpaceshipPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Asteroid.h"

// Sets default values
ASpaceship::ASpaceship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VerticalMove = 0.f;
}

// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();

	ShootingPossible = true;
	FloatingUp = true;
	IsInPlayerInputRotation = true; //Change direction interia simulation (not nessesary)
	StartLocation = GetActorLocation();
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),EngineSound,this->GetActorLocation());
	
}

// Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateToHorizontalIfPossible();
	SimulateFloating();
}

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASpaceship::SidewaysMove);
	PlayerInputComponent->BindAxis(TEXT("Shooting"), this, &ASpaceship::Shooting);
	PlayerInputComponent->BindAction(TEXT("StopMovement"), EInputEvent::IE_Released, this, &ASpaceship::StopMovement);
	PlayerInputComponent->BindAction(TEXT("StartMovement"), EInputEvent::IE_Pressed, this, &ASpaceship::StartMovement);
}

void ASpaceship::SidewaysMove(float AxisValue)
{
	if(!(FMath::Abs(GetActorLocation().Y - StartLocation.Y) >= HorizontalRange && ((GetActorLocation().Y - StartLocation.Y) * AxisValue) > 0)){
		this->AddActorWorldOffset(CT_WorldRightVector*AxisValue*HorizontalSpeed*GetWorld()->DeltaTimeSeconds,true);
	}

	AddInputMoveRotation(AxisValue);
}

void ASpaceship::Shooting(float AxisValue) 
{
	if(AxisValue > 0.f && ShootingPossible){
		FVector BulletSpawnLocation = this->GetActorLocation() + GetActorForwardVector()*100;
		FRotator BulletSpawnRotation = this->GetActorRotation();
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ShotSound,this->GetActorLocation());
		Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass,BulletSpawnLocation,BulletSpawnRotation);
		ShootingPossible = false;
		float ShootDelay = 1.f/ShootingSpeed;
		GetWorldTimerManager().SetTimer(ShootingTimer, this, &ASpaceship::ShootingOn, ShootDelay);
	}
}

void ASpaceship::ShootingOn() 
{
	ShootingPossible = true;
}

void ASpaceship::StartMovement() 
{
	IsInPlayerInputRotation = true;//Change direction interia simulation (not nessesary)
}

void ASpaceship::StopMovement() 
{
	IsInPlayerInputRotation = false;//Change direction interia simulation (not nessesary)
}

void ASpaceship::SimulateFloating()	//Floating Simulation (up and down movement)
{
	if (FloatingUp) {
		if (GetActorLocation().Z <= (StartLocation.Z + CT_FloatingRange))
			VerticalMove = CT_FloatingSpeed;
		else
			FloatingUp = false;
	}
	else {
		if (GetActorLocation().Z >= (StartLocation.Z + -CT_FloatingRange))
			VerticalMove = -CT_FloatingSpeed;
		else
			FloatingUp = true;
	}
	AddActorLocalOffset(FVector(0, 0, VerticalMove), true);
}

void ASpaceship::RotateToHorizontalIfPossible()
{
	//Change direction interia simulation (not nessesary)
	//If actor rotation is not zero and he is not during player input rotation process rotate him back to horizontal pozition
	if (!IsInPlayerInputRotation && FMath::Abs(GetActorRotation().Roll) >= 1.f) {
		int RotateDir = 1;										//Rotate right
		if (GetActorRotation().Roll > 0) { RotateDir = -1; }	//Rotate left
		AddActorLocalRotation(FQuat(FRotator(0, 0, RotateDir * CT_ForwardAxisRotationBackSpeed)), true);
	}
}

void ASpaceship::AddInputMoveRotation(float AxisValue)
{
	//Add spaceship rotation in forward axis when it is moving by player
	if (FMath::Abs(GetActorRotation().Roll) < CT_MaxForwardAxisRoatationAngle && IsInPlayerInputRotation) {
		FRotator SpaceshipRotation = FRotator(0, 0, AxisValue * CT_ForwardAxisRotationSpeed);
		AddActorLocalRotation(FQuat(SpaceshipRotation), true);
		// When Actor is close to max rotation turn on rotation back possibility
		if (FMath::Abs(GetActorRotation().Roll) >= CT_MaxForwardAxisRoatationAngle - (CT_ForwardAxisRotationSpeed * 1.5)) {
			IsInPlayerInputRotation = false;
		}
	}
}

void ASpaceship::DestroyShip() 
{
	AController *PlayerController =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
		PlayerController->GameHasEnded(this, false);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplosionSparks,this->GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ExplosionSound,this->GetActorLocation());
		this->Destroy();
}