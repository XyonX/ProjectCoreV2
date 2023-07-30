/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "Input/CoreInputConfig.h"
#include "InputMappingContext.h"

UCoreInputConfig::UCoreInputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UCoreInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for(const FCoreInputAction& Action : NativeInputActions)
	{
		
		if(Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
		
	}
	if (bLogNotFound)
	{
		//UE_LOG(LogLyra, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
		UE_LOG(LogTemp,Warning,TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this))
	}
	return  nullptr;
	
}

const UInputAction* UCoreInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{

	for(const FCoreInputAction& Action : AbilityInputActions)
	{
		if(Action.InputAction&& Action.InputTag ==InputTag )
		{

			return Action.InputAction;
		}
		
	}
	if (bLogNotFound)
	{
		
		UE_LOG(LogTemp,Warning,TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this))
	}
	return  nullptr;
}


