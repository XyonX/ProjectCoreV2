// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreAbilitySystemComponent.h"
#include "UObject/NoExportTypes.h"
#include"GameplayTagContainer.h"
#include "CoreAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class COREABILITYSYSTEM_API UCoreAbility : public UObject
{
	GENERATED_BODY()
		//#include "CoreAbilitySystemComponent.h"
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	FName AbilityName ;

	UFUNCTION(BlueprintNativeEvent,Category="Ability")
	void OnActivateAbility(AActor*Instigator);
	UFUNCTION(BlueprintNativeEvent,Category="Ability")
	void OnEndAbility(AActor*Instigator);

	UFUNCTION(BlueprintNativeEvent,Category="Ability")
	bool CanStart(AActor*Instigator);
	UFUNCTION()
	UCoreAbilitySystemComponent*GetOwningComp();
	bool bIsRunning;
	UFUNCTION(BlueprintCallable,Category="Ability")
	bool IsRunning()const;
protected:
	//TODO
	//UFUNCTION(BlueprintCallable,Category="Ability")
	//UCoreAbilitySystemComponent*GetOwningComp();
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer GrantTags ;
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer BlockedTags;
	
	
};
