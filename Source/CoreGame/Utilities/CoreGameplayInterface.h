/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoreGameplayInterface.generated.h"

// Deligates for on overlap item with player
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIteractionDelegate ,AActor* ,  PickupObject );

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCoreGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COREGAME_API ICoreGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn*InstigatorPawn);
	
};
