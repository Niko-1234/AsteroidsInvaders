// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceshipPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"



void ASpaceshipPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

	RestartPossible = true;
    FTimerHandle PauseTimer;
    GetWorldTimerManager().SetTimer(PauseTimer, this, &ASpaceshipPlayerController::PauseGame, 2.f);
}

void ASpaceshipPlayerController::SetupInputComponent() 
{
    Super::SetupInputComponent();
    InputComponent->BindAction(TEXT("Restart"), EInputEvent::IE_Pressed, this, &ASpaceshipPlayerController::Restart).bExecuteWhenPaused = true;
    InputComponent->BindAction(TEXT("ExitGame"), EInputEvent::IE_Pressed, this, &ASpaceshipPlayerController::ExitGame).bExecuteWhenPaused = true;
}

void ASpaceshipPlayerController::Restart() 
{
    UGameplayStatics::SetGamePaused(GetWorld(),false);
    FString CurrentMap = GetWorld()->GetMapName();
    if(CurrentMap == CT_SpaceMapEditorName || CurrentMap == CT_SpaceMapInGameName){
        if(RestartPossible)
            RestartLevel();
        else
            UE_LOG(LogTemp, Warning, TEXT("Player still alive, restart impossible"));
    }else if(CurrentMap == CT_MainMenuEditorName || CurrentMap == CT_MainMenuInGameName){
		UGameplayStatics::OpenLevel(GetWorld(), FName(CT_SpaceMapInGameName));
	}else{
		UE_LOG(LogTemp, Warning, TEXT("Failed load map from %s map"), *CurrentMap);
	}
}

void ASpaceshipPlayerController::PauseGame() 
{
    UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
    if (LoseScreen != nullptr)
        LoseScreen->AddToViewport();
        
    UGameplayStatics::SetGamePaused(GetWorld(),true);
}

void ASpaceshipPlayerController::ExitGame() 
{
    FGenericPlatformMisc::RequestExit(false);
}

