// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Plugins/CommonGame/Source/Public/CommonPlayerController.h"
//#include"CommonPlayerController.h"
#include"GameFramework/PlayerController.h"
#include "CorePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COREGAME_API ACorePlayerController : public ACommonPlayerController
{
	GENERATED_BODY()

public:
	// for input bindings
	virtual void SetupInputComponent() override;





	
	
};
