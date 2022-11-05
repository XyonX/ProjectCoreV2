// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CorePawnComponent.h"
#include "GameplayTagContainer.h"
#include "CoreControlComponent.generated.h"

class CorePlayerState;
class UInputComponent;
struct FInputActionValue;
class UCoreInputConfig;

/**
 * ULyraHeroComponent
 *
 *	A component used to create a player controlled pawns (characters, vehicles, etc..).
 */
UCLASS(Blueprintable, Meta=(BlueprintSpawnableComponent))
class COREGAME_API UCoreControlComponent : public UCorePawnComponent
{
	GENERATED_BODY()

public:
	UCoreControlComponent();

	FName NAME_BindInputsNow ;

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);


	void Input_Move (const FInputActionValue & InputActionValue);
	void Input_LookMouse(const FInputActionValue& InputActionValue);
	void Input_LookStick(const FInputActionValue& InputActionValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);
	void Input_AutoRun(const FInputActionValue& InputActionValue);
	
	
};
