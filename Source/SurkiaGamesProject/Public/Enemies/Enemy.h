// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAIController.h"
#include "Enemy.generated.h"

UCLASS()
class SURKIAGAMESPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI")
	class AEnemyAIController* AIController;

	// This will subscribe to the OnMoveCompleted event of the AIController
	void OnAIMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
