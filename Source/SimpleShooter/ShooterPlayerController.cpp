// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    hudScreen = CreateWidget(this, HUDClass);
    if(hudScreen != nullptr)
    {
        hudScreen->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    hudScreen->RemoveFromViewport();

    if(bIsWinner)
    {
        UUserWidget* winScreen = CreateWidget(this, winScreenClass);
        if(winScreen != nullptr)
        {
            winScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* loseScreen = CreateWidget(this, loseScreenClass);
        if(loseScreen != nullptr)
        {
            loseScreen->AddToViewport();
        }
    }
    
    GetWorldTimerManager().SetTimer(restartTimer, this, &APlayerController::RestartLevel, restartDelay);
}