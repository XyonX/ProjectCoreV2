// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CoreAbility.h"

void UCoreAbility::OnActivateAbility_Implementation(AActor*Instigator)
{
	UE_LOG(LogTemp,Warning,TEXT(" Ability ACTIVATED  :%S "),*GetNameSafe(this));

	
}

void UCoreAbility::OnEndAbility_Implementation(AActor*Instigator)
{
	UE_LOG(LogTemp,Warning,TEXT(" Ability Ended  :%S "),*GetNameSafe(this))
}

/*UCoreAbilitySystemComponent* UCoreAbility::GetOwningComp()
{
	
}*/
