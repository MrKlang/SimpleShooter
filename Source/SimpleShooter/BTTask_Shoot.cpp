// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"


UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* controller = OwnerComp.GetAIOwner();

    if(controller == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* characterPawn = Cast<AShooterCharacter>(controller->GetPawn());
    
    if(characterPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    characterPawn->Shoot();

    return EBTNodeResult::Succeeded;
}
