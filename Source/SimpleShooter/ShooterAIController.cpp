// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior!=nullptr)
    {
        APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        startLocation = GetPawn()->GetActorLocation();

        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), startLocation);
    }

}

AShooterAIController::AShooterAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* controlledPawn = Cast<AShooterCharacter>(GetPawn());

    if(controlledPawn != nullptr)
    {
        return controlledPawn->IsDead();
    }

    return true;
}
