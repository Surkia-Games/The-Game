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

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("AwarenessRadius"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(500.0f);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// We bind the OnOverlapBegin event to the OnOverlapBegin method
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// I don't think we need this, but I'm scared to remove this method
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor,UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnOverlapBegin"));

	// We check if the overlapped actor is the player
	if (OtherActor->ActorHasTag("Player"))
	{
		// We get the AIController
		AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());

		// If we have an AIController
		if (AIController)
		{
			// We set the AIState to Chasing
			AIController->SetAIState(EAIState::Chasing);

			// We move to the player's location
			AIController->MoveToActor(OtherActor);
		}
	}
}

