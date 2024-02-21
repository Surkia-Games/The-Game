// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "EnemyAIController.h"
#include "Enemy.generated.h"

UCLASS()
class SURKIAGAMESPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, Category = "Enemy")
	int32 MaxHealth = 100;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	int32 MaxAttackDamage = 10;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ChangeState(EAIState newState);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetTargetLocation(FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void TakeDamage(int32 damage);

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void OnTakeDamage();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void OnDeath();

	/*Attack a character for damage.*/
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void Attack(float damage, ACharacter* character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Die();


private:
	int32 m_Health;
};
