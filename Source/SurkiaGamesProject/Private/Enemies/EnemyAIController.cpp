// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAIController.h"
#include "NavigationSystem.h"

AEnemyAIController::AEnemyAIController()
{
	// Without this, the AIController won't tick (Tick() won't run)
	//PrimaryActorTick.bCanEverTick = true;

	// We get the navigation system using the current world
	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	
	// We create and attach a SphereComponent to use as AttackRadius
	//AttackRadius = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRadius"));
	//AttackRadius->SetupAttachment(GetRootComponent());

	// Create perception component so our enemy can see
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	// Configure sight sense for perception component
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
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

void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnPerceptionUpdated"));
	for (AActor* Actor : UpdatedActors)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *Actor->GetName());
		// Check if the actor is the player
		if (Actor->ActorHasTag("Player"))
		{
			// Check if the player is within the detection range
			if (FVector::Dist(Actor->GetActorLocation(), GetPawn()->GetActorLocation()) <= DetectionRange)
			{
				// Set the AI state to chasing
				SetAIState(EAIState::Chasing);
				
				// Set target NavLocation to a NavLocation at the player's location
				TargetLocation = FNavLocation(Actor->GetActorLocation());
			}
		}
	}
}