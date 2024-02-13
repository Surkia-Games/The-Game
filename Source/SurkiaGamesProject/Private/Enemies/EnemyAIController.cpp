// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAIController.h"
#include "NavigationSystem.h"

AEnemyAIController::AEnemyAIController()
{
	// Without this, the AIController won't tick (Tick() won't run)
	//PrimaryActorTick.bCanEverTick = true;

	// We get the navigation system using the current world
	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	// We start patrolling
	RandomPatrol();
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
	if (GetAIState() == EAIState::Patrolling)
	{
		// We wait for a random amount of time before moving to the next location
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyAIController::RandomPatrol, RandomWaitTime, false);
	}
	else if (GetAIState() == EAIState::Chasing)
	{
		// We keep chasing the player
		MoveToLocation(TargetLocation.Location);
	}
}

void AEnemyAIController::SetTargetLocation(FVector location)
{
	if (!NavSystem->GetRandomPointInNavigableRadius(location, 32, TargetLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find a random point in the radius"));
		return;
	}

	// Prevents jittering
	if (FVector::Dist(location, TargetLocation.Location) < 32)
	{
		return;
	}

	MoveToLocation(TargetLocation.Location);
}