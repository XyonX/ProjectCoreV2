// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CorePawnComponentExtended.h"
#include "CoreAbilitySystemComponent.h"

UCorePawnComponentExtended::UCorePawnComponentExtended()
{

	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	AbilitySystemComponent =nullptr;
	
}

void UCorePawnComponentExtended::InitializeAbilitySystem(UCoreAbilitySystemComponent *InASC, AActor* InOwnerActor)
{

	check(InASC)
	check(InOwnerActor)
 
	if(AbilitySystemComponent == InASC)
	{

		// The ability system component hasn't changed.
		return ; 
	}
	if (AbilitySystemComponent)
	{
		// Clean up the old ability system component.
		UninitializeAbilitySystem();
	}
	APawn* Pawn = GetPawnChecked<APawn>();
	AActor* ExistingAvatar = InASC->GetAvatarActor();
/*
	if ((ExistingAvatar != nullptr) && (ExistingAvatar != Pawn))
	{
		UE_LOG(LogLyra, Log, TEXT("Existing avatar (authority=%d)"), ExistingAvatar->HasAuthority() ? 1 : 0);

		// There is already a pawn acting as the ASC's avatar, so we need to kick it out
		// This can happen on clients if they're lagged: their new pawn is spawned + possessed before the dead one is removed
		ensure(!ExistingAvatar->HasAuthority());

		if (ULyraPawnExtensionComponent* OtherExtensionComponent = FindPawnExtensionComponent(ExistingAvatar))
		{
			OtherExtensionComponent->UninitializeAbilitySystem();
		}
	}*/
	

	
}

void UCorePawnComponentExtended::UninitializeAbilitySystem()
{
}


