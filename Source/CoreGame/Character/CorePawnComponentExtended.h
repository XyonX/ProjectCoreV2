// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CorePawnComponent.h"
#include "CorePawnComponentExtended.generated.h"


class UCoreAbilitySystemComponent ;

UCLASS()
class COREGAME_API UCorePawnComponentExtended : public UCorePawnComponent
{
	GENERATED_BODY()

public:
	UCorePawnComponentExtended();
	static UCorePawnComponentExtended* FindPawnExtensionComponent (const AActor* Actor ) {return Actor ? Actor->FindComponentByClass<UCorePawnComponentExtended>() : nullptr;}

	UCoreAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; };

	// Should be called by the owning pawn to become the avatar of the ability system.
	void InitializeAbilitySystem(UCoreAbilitySystemComponent *InASC, AActor* InOwnerActor);

	// Should be called by the owning pawn to remove itself as the avatar of the ability system.
	void UninitializeAbilitySystem();
	
protected:

	UPROPERTY()
	UCoreAbilitySystemComponent* AbilitySystemComponent ; 
	
};
