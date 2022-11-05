// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "AttributeSet.generated.h"


USTRUCT(BlueprintType)
struct FCoreAttributeData
{
	GENERATED_BODY()
	FCoreAttributeData() : BaseValue(0.0f) , CurrentValue(0.0f) {}
	FCoreAttributeData( float DefaultValue) : BaseValue(DefaultValue) , CurrentValue(DefaultValue) {}


	//virtual ~FGameplayAttributeData() {} 
	

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float BaseValue;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float CurrentValue;
	
};

/** Describes a FGameplayAttributeData or float property inside an attribute set. Using this provides editor UI and helper functions */
// Actually Stores Multiple FCoreAtteibteData 
/*USTRUCT(BlueprintType)
struct FCoreAttribute
{
	GENERATED_BODY()

	//FCoreAttribute(FProperty *NewProperty);

private:
	//friend class FAttributePropertyDetails;

	//UPROPERTY(Category = GameplayAttribute, EditAnywhere)
	//TFieldPath<FProperty> Attribute;
	//FProperty*	Attribute;

	//UPROPERTY(Category = GameplayAttribute, VisibleAnywhere)
	//UStruct* AttributeOwner;
	
};*/



/**
 * Defines the set of all GameplayAttributes for your game
 * Games should subclass this and add FGameplayAttributeData properties to represent attributes like health, damage, etc
 * AttributeSets are added to the actors as subobjects, and then registered with the AbilitySystemComponent
 * It often desired to have several sets per project that inherit from each other
 * You could make a base health set, then have a player set that inherits from it and adds more attributes
 */

UCLASS()
class COREABILITYSYSTEM_API UAttributeSet : public UObject
{
	GENERATED_BODY()
	
	
};

/*
USTRUCT(BlueprintType)
struct  FCoreAttributeMetaData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FCoreAttributeMetaData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	float		BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	float		MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	float		MaxValue;

	UPROPERTY()
	FString		DerivedAttributeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")
	bool		bCanStack;
};
*/