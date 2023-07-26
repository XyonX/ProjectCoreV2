#pragma once

#include "GameFramework/GameMode.h"
#include "LoadingScreenGameMode.generated.h"


UCLASS(Blueprintable)
class COREGAMEMANAGER_API ALoadingScreenGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoadingScreenGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};