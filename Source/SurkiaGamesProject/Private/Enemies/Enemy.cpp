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
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::ChangeState(EAIState newState)
{
	// We get the AIController and cast it to our custom AIController
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());

	// If we have a valid AIController
	if (AIController)
	{
		// We set the new state
		AIController->SetAIState(newState);
	}
}

void AEnemy::SetTargetLocation(FVector newLocation)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());

	if (AIController)
	{
		AIController->SetTargetLocation(newLocation);
	}
}