// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurkiaGamesProjectPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "SurkiaGamesProjectCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASurkiaGamesProjectPlayerController::ASurkiaGamesProjectPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ASurkiaGamesProjectPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ASurkiaGamesProjectPlayerController::SetupInputComponent()
{
}

void ASurkiaGamesProjectPlayerController::OnInputStarted()
{
}

// Triggered every frame when the input is held down
void ASurkiaGamesProjectPlayerController::OnSetDestinationTriggered()
{
}

void ASurkiaGamesProjectPlayerController::OnSetDestinationReleased()
{
}

// Triggered every frame when the input is held down
void ASurkiaGamesProjectPlayerController::OnTouchTriggered()
{
}

void ASurkiaGamesProjectPlayerController::OnTouchReleased()
{
}
