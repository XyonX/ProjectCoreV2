// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CoreControlComponent.h"

#include "CoreAbilitySystemComponent.h"
#include "CorePawnComponentExtended.h"


// Constructor
UCoreControlComponent::UCoreControlComponent()
{
	
}

void UCoreControlComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCoreControlComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UCoreControlComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(const APawn*Pawn = GetPawn<APawn>())
	{
		if(const UCorePawnComponentExtended * PawnExtensionComp = UCorePawnComponentExtended::FindPawnExtensionComponent(Pawn))
		{
			if(UCoreAbilitySystemComponent * CoreASC = PawnExtensionComp->GetAbilitySystemComponent())
			{
				//TODO
				//CoreASC->AbilityInputTagPressed (InputTag);
			}
		}
		
	}
}

void UCoreControlComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	const APawn* Pawn  = GetPawn<APawn>();
	if(!Pawn)
	{

		return ;
	}
	if(const UCorePawnComponentExtended*  PawnExtentionComp = UCorePawnComponentExtended::FindPawnExtensionComponent(Pawn))
	{

		if(UCoreAbilitySystemComponent * CoreASC = PawnExtentionComp->GetAbilitySystemComponent() )
		{
			//TODO
			//CoreASC->AbilityInputTagReleased(InputTag);
		}
	}
}

void UCoreControlComponent::Input_Move(const FInputActionValue& InputActionValue)
{
}

void UCoreControlComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
}

void UCoreControlComponent::Input_LookStick(const FInputActionValue& InputActionValue)
{
}

void UCoreControlComponent::Input_Crouch(const FInputActionValue& InputActionValue)
{
}

void UCoreControlComponent::Input_AutoRun(const FInputActionValue& InputActionValue)
{
}
