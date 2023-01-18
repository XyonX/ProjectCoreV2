// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreAbilitySystemComponent.h"
#include "Abilities/CoreAbility.h"
#include "Animation/Rig.h"

// Sets default values for this component's properties
UCoreAbilitySystemComponent::UCoreAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCoreAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//GainedAbilities = GainedAbilities.Append(inheritedAbility);
	
}
void UCoreAbilitySystemComponent::GainAbility(AActor* Instigator, TSubclassOf<UCoreAbility> AbilityClass)
{
	if(!ensure(AbilityClass))
	{
		return;
		UE_LOG(LogTemp,Warning,TEXT("Ability IS NOT VALID ENSURE FAILED"))
		
	}
	UCoreAbility* NewAbility =  NewObject<UCoreAbility>(this,AbilityClass);
	if(NewAbility)
	{

		GainedAbilities.Add(NewAbility);
		UE_LOG(LogTemp,Warning,TEXT("Ability  Gained :  %s") , *NewAbility->GetName())
	}
	
}
void UCoreAbilitySystemComponent::LoseAbility(UCoreAbility* AbilityClass)
{
	
}

bool UCoreAbilitySystemComponent::StartAbility_ByName(AActor* InstigatorActor, FName AbilityName)
{
	for (UCoreAbility* Ability : GainedAbilities)
	{
		if(Ability  && Ability->AbilityName == AbilityName)
		{
			if(!Ability->CanStart(InstigatorActor))
			{
				UE_LOG(LogTemp,Warning,TEXT("Ability Couldnt Start :  %s") , *Ability->GetName())
				continue;
			}
			UE_LOG(LogTemp,Warning,TEXT("Ability  Started :  %s") , *Ability->GetName())
			Ability->OnActivateAbility(InstigatorActor);
			
			return true ;
			}

		
	}
	return false;
	
}
bool UCoreAbilitySystemComponent::StopAbilityByName(AActor* InstigatorActor, FName AbilityName)
{
	for (UCoreAbility* Ability : GainedAbilities)
	{
		if(Ability  && Ability->AbilityName == AbilityName)
		{

			Ability->OnEndAbility(InstigatorActor);
			return true ;
		}
	}
	return false;
}

bool UCoreAbilitySystemComponent::StartAbility_Class(AActor* InstigatorActor, TSubclassOf<UCoreAbility>AbilityClass)
{
	UE_LOG(LogTemp,Warning,TEXT(" Start Ability Function Called"))
	for(UCoreAbility * Ability : GainedAbilities )
	{
		//if(Ability && Ability->IsA(AbilityClass))
		if(Ability && Ability->GetClass() == AbilityClass)
			
		{
			if(!Ability->CanStart(InstigatorActor))
			{
				UE_LOG(LogTemp,Warning,TEXT("Ability Couldnt Start :  %s") , *Ability->GetName())
				continue;
			}
			Ability ->OnActivateAbility(InstigatorActor);
			UE_LOG(LogTemp,Warning,TEXT("Ability  Started :  %s") , *Ability->GetName())
			return true ;
		}
		
	}
	return false ;
}

bool UCoreAbilitySystemComponent::StopAbility_Class(AActor* InstigatorActor, TSubclassOf<UCoreAbility> AbilityClass)
{
	for(UCoreAbility * Ability : GainedAbilities )
	{

		if(Ability && Ability->IsA(AbilityClass))
		{
			if(Ability->IsRunning())
			{
				Ability ->OnEndAbility(InstigatorActor);
				return true ;
			}
			
		}
		
	}
	return false ;
}







// Called every frame
void UCoreAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCoreAbilitySystemComponent::SetOwnerActor(AActor* NewOwnerActor)
{
	if(NewOwnerActor)
	{
		OwnerActor =NewOwnerActor;
	}
}

AActor* UCoreAbilitySystemComponent::GetOwnerActor() const
{
return OwnerActor;
}

AActor* UCoreAbilitySystemComponent::GetAvatarActor() const
{
	return  AvatarActor;
	
}

void UCoreAbilitySystemComponent::SetAvatarActor(AActor* InAvatarActor)
{
	if(InAvatarActor)
	{
		AvatarActor = InAvatarActor ;
	}
}

/*UAttributeSet* UCoreAbilitySystemComponent::GetAttributeSubobject(const TSubclassOf<UAttributeSet> AttributeSetclass)
{
	for(UAttributeSet * Set : SpawnedAttributes )
	{

		if(Set && Set->IsA(AttributeSetclass) )
		{
			return Set ;
		}
		
	}
	return nullptr ;
}*/

/*
void UCoreAbilitySystemComponent::SetSpawnedAttributes(const TArray<UAttributeSet*>& NewAttributeSet)
{
	
}

const TArray<UAttributeSet*>& UCoreAbilitySystemComponent::GetSpawnedAttributes() const
{
	return SpawnedAttributes;
}*/

