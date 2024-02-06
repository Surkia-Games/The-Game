// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Navigation/PathFollowingComponent.h"
#include "Enemies/EnemyAIController.h"
#include "AITypes.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AEnemyAIController>(GetController());

	// We tell the AI to move to a random location
	AIController->RandomPatrol();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//int state = static_cast<int>(AIController->GetAIState());
	switch (AIController->GetAIState())
	{
		case EAIState::Idle:
			// Do nothing
			break;
		case EAIState::Patrolling:
			// Do nothing
			break;
		case EAIState::Chasing:
			// Do nothing
			break;
		case EAIState::Attacking:
			// Do nothing
			break;
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// I don't think we need this, but I'm scared to remove this method
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

}

