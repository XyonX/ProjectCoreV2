// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ItemSystem/Item/Item_Base.h"
#include "Item_Weapon.generated.h"


UENUM()
enum class EWeaponMode : uint8
{
	SingleFire		UMETA(DisplayName = " Single Shot"),
	AutoFire      UMETA(DisplayName = "Auto Fire "),
	
	
};


UCLASS()
class COREGAME_API AItem_Weapon : public AItem_Base
{
	GENERATED_BODY()
	AItem_Weapon();

public:
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Reference")
	//class ACoreCharacter*OwnerCharacter;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	USkeletalMeshComponent*WeaponMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*Mag;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*Muzzle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*Sight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*ForeGrip;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*ButtStock;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	int Ammo ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	EWeaponPosition WeaponPosition ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	bool bIsOnHand ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	class UDataTable* WeaponDatTable;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName MagSocketName;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName MuzzleSocketName;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName SightSocketName ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName ForeGripSocketName ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName ButtStockSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName CharacterSocket;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName HandIKSocket ;
	//UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	//FItemWeapon	WeaponItemData ;
	FGameplayTagContainer WeaponTags;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	EWeaponType WeaponType ;

	UFUNCTION(BlueprintCallable)
	void Init_Weapon_Item(FName IDD);
	//FName GetPlayerS

	FORCEINLINE UDataTable* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path.ToString()));
	}
	
	FItemWeapon* GetWeaponDataFromID(FName IDD);
	FItemWeapon* GetWeaponData();
	FORCEINLINE FName GetID () {return ID;}
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PickupWeapon")
	FVector IKHandSocketLocation ;
	UFUNCTION(BlueprintCallable)
	FVector GetHandSocketLocation();

	
	
	
	
	
};
