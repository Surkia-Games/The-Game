// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NavigationSystem.h"
#include "EnemyAIController.generated.h"

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

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attacking")
	USphereComponent* AttackRadius;

	class UNavigationSystemV1* NavSystem;
	FVector RandomLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float RandomWaitTime = 5.0f;

	void RandomPatrol();

	EAIState GetAIState() const { return AIState; }
	void SetAIState(EAIState NewState) { AIState = NewState; }

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float PatrolRadius = 1000.0f;

private:
	EAIState AIState = EAIState::Idle;
	FNavLocation TargetLocation;
};
