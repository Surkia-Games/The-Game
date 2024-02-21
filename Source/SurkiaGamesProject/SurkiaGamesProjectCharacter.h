// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurkiaGamesProjectCharacter.generated.h"

UCLASS(Blueprintable)
class ASurkiaGamesProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASurkiaGamesProjectCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
};

