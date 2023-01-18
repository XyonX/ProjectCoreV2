// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemSystem/ItemObjects/Item_Weapon.h"
#include "CoreInventorySystemComponent.generated.h"


UENUM()
enum EWeaponSlot
{
	Null = 0		UMETA(DisplayName = "Null"),
	Primary = 1		UMETA(DisplayName = "Primary"),
	Secondary=2		UMETA(DisplayName = "Secondary"),
	Melee = 3		UMETA(DisplayName = "Melee"),	
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COREGAME_API UCoreInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoreInventorySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AItem_Weapon* PlayerEquippedWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AItem_Weapon* Weapon1_Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AItem_Weapon* Weapon2_Secondary;
	EWeaponSlot EquippedWeaponSlot;
	FName WeaponIDs[3] ;
	ACoreCharacter*GetOwnerCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bHasWeaponEquipped ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName CharacterWeaponSocketName;
	
	void EquipWeapon(EWeaponSlot WeaponSlot);
	void UnEquipWeapon();
	void EquipWeaponFromID(AItem_Weapon*Weapon);
	void SwapWeapon (EWeaponSlot WeaponSlotToSwapNewWeapon);
	void EqUnEq_Primary();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bWeaponShouldIdle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bWeaponShouldAim ;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	//EEquipWeaponPosition WeaponHoldingPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int WaitingTime ;
	//FTimerHandle WeaponPositionTimerHandle
	//void SetWeaponPosition();
	FORCEINLINE UDataTable* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path.ToString()));
	}
	ACoreCharacter*OwnerCharacter ;


	// montages

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage* AM_Idle_Equip_Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage* AM_Equip_Idle_Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage* AM_Swap_Primary;
	
	
};
