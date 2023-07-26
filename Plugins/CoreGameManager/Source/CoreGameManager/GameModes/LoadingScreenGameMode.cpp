// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreenGameMode.h"
#include "CoreGameManager/Pawn/UIPawn.h"
#include "CoreGameManager/Player/UIPlayerController.h"

ALoadingScreenGameMode::ALoadingScreenGameMode(const FObjectInitializer& ObjectInitializer)
{
	DefaultPawnClass=AUIPawn::StaticClass();
	PlayerControllerClass= AUIPlayerController::StaticClass();
}

void ALoadingScreenGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ALoadingScreenGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
