// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

UENUM(BlueprintType, Category = "AI")
enum class EAIState : uint8
{
	Idle,
	Patrolling,
	Chasing,
	Attacking
};

UCLASS()
class SURKIAGAMESPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	void BeginPlay() override;

	class UNavigationSystemV1* NavSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float RandomWaitTime = 5.0f;

	void RandomPatrol();

	EAIState GetAIState() const { return AIState; }
	void SetAIState(EAIState NewState) { AIState = NewState; }

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void SetTargetLocation(FVector NewLocation);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float PatrolRadius = 1000.0f;

private:
	// State of the enemy AI
	EAIState AIState = EAIState::Idle;

	// Current target NavLocation
	FNavLocation TargetLocation;

	float GetRemainingPathLength() const;
};
