// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Sprint.h"

#include "Character/CoreCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGA_Sprint::OnActivateAbility_Implementation(AActor* Instigator)
{
	Super::OnActivateAbility_Implementation(Instigator);
	ACoreCharacter*CoreCharacter = Cast<ACoreCharacter>(Instigator);
	if(CoreCharacter)
	{
		DefaultWalk_Speed=CoreCharacter->GetCharacterMovement()->MaxWalkSpeed;
		CoreCharacter->GetCharacterMovement()->MaxWalkSpeed=Sprint_Speed;
		UCoreAbilitySystemComponent*Comp = GetOwningComponent();
		Comp->ActiveGameplayTags.AppendTags(GrantTags);
	}
}

void UGA_Sprint::OnEndAbility_Implementation(AActor* Instigator)
{
	Super::OnEndAbility_Implementation(Instigator);
	ACoreCharacter*CoreCharacter = Cast<ACoreCharacter>(Instigator);
	if(CoreCharacter)
	{
		CoreCharacter->GetCharacterMovement()->MaxWalkSpeed=DefaultWalk_Speed;
		UCoreAbilitySystemComponent*Comp = GetOwningComponent();
		Comp->ActiveGameplayTags.RemoveTags(GrantTags);
		
	}
	
}

UCoreAbilitySystemComponent* UGA_Sprint::GetOwningComponent() const
{
	return Cast<UCoreAbilitySystemComponent>(GetOuter());
}
