// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAIController.h"
#include "NavigationSystem.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	AttackRadius = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRadius"));
	AttackRadius->SetupAttachment(GetRootComponent());
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::RandomPatrol()
{
	if (!NavSystem)
		return;

	NavSystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), PatrolRadius, TargetLocation);

	MoveToLocation(TargetLocation.Location);

	SetAIState(EAIState::Patrolling);
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	SetAIState(EAIState::Idle);

	Super::OnMoveCompleted(RequestID, Result);
}