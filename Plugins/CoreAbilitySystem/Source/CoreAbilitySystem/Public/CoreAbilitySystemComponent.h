// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AttributeSet.h"
#include "CoreAbilitySystemComponent.generated.h"

class UCoreAbility ;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityStateChanged ,UCoreAbilitySystemComponent*,OwningComp ,UCoreAbility*,Ability);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COREABILITYSYSTEM_API UCoreAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoreAbilitySystemComponent();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tags")
	FGameplayTagContainer ActiveGameplayTags;

	// this Will Gain the Ability In Your Character I  MEAN IN THE COMPONENT 
	UFUNCTION(BlueprintCallable,Category="Ability")
	void GainAbility(AActor* Instigator , TSubclassOf<UCoreAbility>AbilityClass);
	//This Will Remove Ability From Class
	UFUNCTION(BlueprintCallable,Category="Ability")
	void LoseAbility(UCoreAbility*AbilityClass);

	// This will call the abiity By Namew
	UFUNCTION(BlueprintCallable,Category="Ability")
	bool StartAbility_ByName(AActor*InstigatorActor ,FName AbilityName );
	UFUNCTION(BlueprintCallable,Category="Ability")
	bool StopAbilityByName(AActor*InstigatorActor ,FName AbilityName);
	UFUNCTION(BlueprintCallable,Category="Ability")
	bool StartAbility_Class ( AActor*InstigatorActor , TSubclassOf<UCoreAbility> AbilityClass) ;
	UFUNCTION(BlueprintCallable,Category="Ability")
	bool StopAbility_Class ( AActor*InstigatorActor , TSubclassOf<UCoreAbility> AbilityClass) ;

	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	TArray<TSubclassOf<UCoreAbility>>inheritedAbility;
	UPROPERTY()
	TArray<UCoreAbility*>GainedAbilities;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityStarted ;
	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityStoped ;


	// ATTRIBUTE
	
	//UPROPERTY(EditAnywhere, Category="AttributeTest")
	//TArray<FAttributeDefaults>	DefaultStartingData;

	/** List of attribute sets */
	UPROPERTY()
	TArray<UAttributeSet*>	SpawnedAttributes;

	//UAttributeSet* GetAttributeSubobject (const TSubclassOf<UAttributeSet> AttributeSet) ;
	/*
	template<class T>
	const T* GetAttributeSet ()
	{
		return (T*)GetAttributeSubobject(T::StaticClass());
	}*/
	//TSubclassOf<UAttributeSet*>  GetAttributeSubobject ();
	
	
	
	//void SetSpawnedAttributes(const TArray<UAttributeSet*>& NewAttributeSet);
	//TArray<UAttributeSet*>& GetSpawnedAttributes_Mutable();
	//const TArray<UAttributeSet*>& GetSpawnedAttributes() const;


	// ACTOR INTERACTION


	/** Cached off data about the owning actor that abilities will need to frequently access (movement component, mesh component, anim instance, etc) */
	//TSharedPtr<FGameplayAbilityActorInfo>	AbilityActorInfo;

	/**
	 *	Initialized the Abilities' ActorInfo - the structure that holds information about who we are acting on and who controls us.
	 *      OwnerActor is the actor that logically owns this component.
	 *		AvatarActor is what physical actor in the world we are acting on. Usually a Pawn but it could be a Tower, Building, Turret, etc, may be the same as Owner
	 */
	//virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor);

	
	/** The actor that owns this component logically */
	UE_DEPRECATED(4.26, "This will be made private in future engine versions. Use SetOwnerActor or GetOwnerActor instead.")
	//ReplicatedUsing = OnRep_OwningActor
	UPROPERTY()
	AActor* OwnerActor;

	void SetOwnerActor(AActor* NewOwnerActor);
	AActor* GetOwnerActor() const;

	UE_DEPRECATED(4.26, "This will be made private in future engine versions. Use SetAvatarActor or GetAvatarActor instead.")
	/** The actor that is the physical representation used for abilities. Can be NULL */
	//ReplicatedUsing = OnRep_OwningActor
	UPROPERTY()
	AActor* AvatarActor;
	
	/** Returns the avatar actor for this component */
	AActor* GetAvatarActor() const;

	/** Changes the avatar actor, leaves the owner actor the same */
	void SetAvatarActor(AActor* InAvatarActor);

};
