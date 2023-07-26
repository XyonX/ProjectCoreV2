// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreenGameMode.h"
#include "CoreGameManager/Pawn/UIPawn.h"
#include "CoreGameManager/Player/UIPlayerController.h"
#include "CoreGameManager/UISpawner/LoadingScreenUISpawner.h"

ALoadingScreenGameMode::ALoadingScreenGameMode(const FObjectInitializer& ObjectInitializer)
{
	DefaultPawnClass=AUIPawn::StaticClass();
	PlayerControllerClass= AUIPlayerController::StaticClass();
}

void ALoadingScreenGameMode::BeginPlay()
{
	Super::BeginPlay();
	BeginPlayEvent();
/*
	UWorld* World = GetWorld();

	if (World)
	{
		// Define the spawn parameters, you can leave it as the default or customize it as needed.
		FActorSpawnParameters SpawnParams;

		// Set the spawn location and rotation for the new actor instance.
		FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn the actor in the world using the actor class and provided location/rotation.
		ALoadingScreenUISpawner* UISpawner = World->SpawnActor<ALoadingScreenUISpawner>(ALoadingScreenUISpawner::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	};*/
	
}

void ALoadingScreenGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
