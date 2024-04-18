// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAIController.h"
#include "NavigationSystem.h"
#include "AbstractNavData.h"
#include "NavigationData.h"
#include "NavigationPath.h"
#include "Navigation/PathFollowingComponent.h"

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

	if (GetRemainingPathLength() > 0.5f)
		return;

	if (NavSystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), PatrolRadius, TargetLocation))
	{
		MoveToLocation(TargetLocation.Location);

		SetAIState(EAIState::Patrolling);
	}
	else
	{
		SetAIState(EAIState::Idle);
	}
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.Code == EPathFollowingResult::Success)
	{
		// We reached the target location
		SetAIState(EAIState::Idle);
		if (GetAIState() == EAIState::Patrolling)
		{
			// We wait for a random amount of time before moving to the next location
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyAIController::RandomPatrol, RandomWaitTime, false);
		}
		else if (GetAIState() == EAIState::Chasing)
		{
			if(FVector::Dist(TargetLocation.Location, GetPawn()->GetActorLocation()) > 100.0f)
				MoveToLocation(TargetLocation.Location);
		}
	}
	else
	{
		// We failed to reach the target location
		SetAIState(EAIState::Idle);
	}
}

void AEnemyAIController::SetTargetLocation(FVector location)
{
	if (FVector::Dist(GetPawn()->GetActorLocation(), location) < 100.0f)
		return;

	MoveToLocation(location);
}

float AEnemyAIController::GetRemainingPathLength() const
{
	if (NavSystem == nullptr)
		return 0.0f;

	UPathFollowingComponent* PathFollower = GetPathFollowingComponent();

	if (PathFollower == nullptr)
		return 0.0f;

	const FNavPathSharedPtr Path = PathFollower->GetPath();

	if (Path == nullptr)
		return 0.0f;

	float Length = 0.0f;

	TArray<FNavPathPoint> PathPoints = Path->GetPathPoints();

	if (PathPoints.Num() < 2)
		return 0.0f;

	for (int32 i = 0; i < PathPoints.Num() - 1; i++)
	{
		Length += FVector::Dist(PathPoints[i].Location, PathPoints[i + 1].Location);
	}

	return Length;
}