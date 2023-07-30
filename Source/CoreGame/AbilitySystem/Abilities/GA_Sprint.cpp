/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "AbilitySystem/Abilities/GA_Sprint.h"

//#include "Character/CoreCharacter.h"
//#include "Character/CoreCharacterEXTENDED.h"
#include "GameFramework/CharacterMovementComponent.h"
/*
void UGA_Sprint::OnActivateAbility_Implementation(AActor* Instigator)
{
	Super::OnActivateAbility_Implementation(Instigator);
	ACoreCharacterEXTENDED*CoreCharacter = Cast<ACoreCharacterEXTENDED>(Instigator);
	if(CoreCharacter)
	{
		DefaultWalk_Speed=CoreCharacter->GetCharacterMovement()->MaxWalkSpeed;
		if(CoreCharacter->bHasWeaponEquipped)
		{
			if (bWantToUSeSameSpeedForWeaponSprint)
			{
				CoreCharacter->GetCharacterMovement()->MaxWalkSpeed=Sprint_Speed;
			}
			else
				CoreCharacter->GetCharacterMovement()->MaxWalkSpeed=CoreCharacter->DefaultMovementSpeed.Jog;
				
		}
		else
		{
			if(bWantToUSeCustomSpeed )
			{
				CoreCharacter->GetCharacterMovement()->MaxWalkSpeed=Sprint_Speed;
			
			}
			else
				CoreCharacter->GetCharacterMovement()->MaxWalkSpeed=CoreCharacter->DefaultMovementSpeed.Jog;
		
			UCoreAbilitySystemComponent*Comp = GetOwningComponent();
			Comp->ActiveGameplayTags.AppendTags(GrantTags);
		}
		
	}
}

void UGA_Sprint::OnEndAbility_Implementation(AActor* Instigator)
{
	Super::OnEndAbility_Implementation(Instigator);
	ACoreCharacterEXTENDED*CoreCharacter = Cast<ACoreCharacterEXTENDED>(Instigator);
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
}*/
