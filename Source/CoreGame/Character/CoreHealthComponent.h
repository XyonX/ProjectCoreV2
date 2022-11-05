// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreAbilitySystemComponent.h"
#include "Components/GameFrameworkComponent.h"
#include "CoreHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoreHealth_DeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FCoreHealth_AttributeChanged, UCoreHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

class UCoreAbilitySystemComponent ;

/**
 * ELyraDeathState
 *
 *	Defines current state of death.
 */
UENUM(BlueprintType)
enum class ECoreDeathState : uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

UCLASS()
class COREGAME_API UCoreHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:

	// THESE TWO FUNCTION IS FOR INITIALIZE AND UNINITIALIZE
	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "CORE|Health")
	void InitializeWithAbilitySystem(UCoreAbilitySystemComponent* InASC);

	// Uninitialize the component, clearing any references to the ability system.
	UFUNCTION(BlueprintCallable, Category = "CORE|Health")
	void UninitializeFromAbilitySystem();

	
	// Returns the current health value.
	UFUNCTION(BlueprintCallable, Category = "CORE|Health")
	float GetHealth() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable, Category = "CORE|Health")
	float GetMaxHealth() const;

	
	//UFUNCTION(BlueprintCallable, Category = "CORE|Health")
	//ECoreDeathState GetDeathState() const { return DeathState; }

	//UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Lyra|Health", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	//bool IsDeadOrDying() const { return (DeathState > ELyraDeathState::NotDead); }

	// Begins the death sequence for the owner.
	//virtual void StartDeath();

	// Ends the death sequence for the owner.
	//virtual void FinishDeath();
	

public:

	// Delegate fired when the health value has changed.
	UPROPERTY(BlueprintAssignable)
	FCoreHealth_AttributeChanged OnHealthChanged;

	// Delegate fired when the max health value has changed.
	UPROPERTY(BlueprintAssignable)
	FCoreHealth_AttributeChanged OnMaxHealthChanged;

	// Delegate fired when the death sequence has started.
	UPROPERTY(BlueprintAssignable)
	FCoreHealth_DeathEvent OnDeathStarted;

	// Delegate fired when the death sequence has finished.
	UPROPERTY(BlueprintAssignable)
	FCoreHealth_DeathEvent OnDeathFinished;

protected:
	UPROPERTY()
	UCoreAbilitySystemComponent*AbilitySystemComponent ;

	// Health set used by this component.
	//TODO   Make Attribute / CoreHealthState
	//UPROPERTY() 
	//const UCoreHealthSet* HealthSet;
	
};
