// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreAbilitySystemComponent.h"
#include "Abilities/CoreAbility.h"
#include "GA_Sprint.generated.h"

/**
 * 
 */
UCLASS()
class COREGAME_API UGA_Sprint : public UCoreAbility
{
	GENERATED_BODY()

public:

	virtual void OnActivateAbility_Implementation(AActor* Instigator) override;
	virtual void OnEndAbility_Implementation(AActor* Instigator) override;

	float Sprint_Speed = 1000.0f ;
	float DefaultWalk_Speed =600.0f;
	
	UCoreAbilitySystemComponent*GetOwningComponent()const;
	
	
	
	
};
