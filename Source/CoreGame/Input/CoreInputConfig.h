/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CoreInputConfig.generated.h"

class UInputAction ;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FCoreInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};
/**
 * ULyraInputConfig
 *
 *	Non-mutable data asset that contains input configuration properties.
 */
UCLASS()
class COREGAME_API UCoreInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UCoreInputConfig(const FObjectInitializer& ObjectInitializer);
	
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FCoreInputAction> NativeInputActions;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and are automatically bound to abilities with matching input tags.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FCoreInputAction> AbilityInputActions;
};
