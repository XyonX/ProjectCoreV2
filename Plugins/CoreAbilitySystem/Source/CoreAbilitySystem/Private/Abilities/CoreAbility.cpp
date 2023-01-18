// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CoreAbility.h"

void UCoreAbility::OnActivateAbility_Implementation(AActor*Instigator)
{
	UE_LOG(LogTemp,Warning,TEXT(" Ability ACTIVATED  :%S "),*GetNameSafe(this));
	UCoreAbilitySystemComponent* Comp = GetOwningComp();
	Comp->ActiveGameplayTags.AppendTags(GrantTags);

	bIsRunning = true;
	
}

void UCoreAbility::OnEndAbility_Implementation(AActor*Instigator)
{
	UE_LOG(LogTemp,Warning,TEXT(" Ability Ended  :%S "),*GetNameSafe(this))
	ensureAlways(bIsRunning);
	UCoreAbilitySystemComponent* Comp = GetOwningComp();
	Comp->ActiveGameplayTags.RemoveTags(GrantTags);
	bIsRunning = false;
}

/*UCoreAbilitySystemComponent* UCoreAbility::GetOwningComp()
{
	
}*/
bool UCoreAbility::CanStart_Implementation(AActor* Instigator)
{
 UCoreAbilitySystemComponent*AbilitySystemComp=	GetOwningComp();
	if(AbilitySystemComp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Cant start true for :  %s"), *this->GetName()));	
	return true;
	
	
}

UCoreAbilitySystemComponent* UCoreAbility::GetOwningComp()
{
	return   Cast <UCoreAbilitySystemComponent>(GetOuter());
}

bool UCoreAbility::IsRunning() const
{
	return bIsRunning;
}
