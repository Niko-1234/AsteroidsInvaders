// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpaceshipPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDSINVADERS_API ASpaceshipPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	bool RestartPossible = false;

//Class constants
private:
	//Maps names
	const FString CT_MainMenuEditorName = TEXT("UEDPIE_0_MainMenu");
	const FString CT_MainMenuInGameName = TEXT("MainMenu");
	const FString CT_SpaceMapEditorName = TEXT("UEDPIE_0_SpaceMap");
	const FString CT_SpaceMapInGameName = TEXT("SpaceMap");

public:
	UFUNCTION(BlueprintCallable)
	void Restart();

private:
	void PauseGame();
	void ExitGame();
	
};
