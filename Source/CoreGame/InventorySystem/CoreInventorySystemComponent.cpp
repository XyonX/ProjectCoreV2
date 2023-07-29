// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem/CoreInventorySystemComponent.h"
//#include "Character/CoreCharacterEXTENDED.h"

#include "InteractionSystem/CoreInteractionComponent.h"

// Sets default values for this component's properties
UCoreInventorySystemComponent::UCoreInventorySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

/*
// Called when the game starts
void UCoreInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor*OwnerActor  = GetOwner();
	OwnerCharacter = Cast<ACoreCharacterEXTENDED>(OwnerActor);
	
}


// Called every frame
void UCoreInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ACoreCharacterEXTENDED* UCoreInventorySystemComponent::GetOwnerCharacter()
{
	AActor*OwnerActor  = GetOwner();
	OwnerCharacter = Cast<ACoreCharacterEXTENDED>(OwnerActor);
	return OwnerCharacter ;
}

void UCoreInventorySystemComponent::EquipWeapon( EWeaponSlot WeaponSlot)
{
	
	if(bHasWeaponEquipped)
	{
		//SwapWeapon();
		
	}
	if(!bHasWeaponEquipped )
	{
		EquippedWeaponSlot =WeaponSlot;
	
		if(WeaponSlot == EWeaponSlot::Primary && Weapon1_Primary )
		{
			bHasWeaponEquipped = true;
			OwnerCharacter->bHasWeaponEquipped = true;
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Weapon 1 is available and Weapon Equiping from primary slot  !"));

			PlayerEquippedWeapon = Weapon1_Primary;
			PlayerEquippedWeapon->SetHidden(false);
			//Weapon1_Primary->Init_Weapon_Item(WeaponIDs[1]);
			PlayerEquippedWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CharacterWeaponSocketName);
		}
		if(WeaponSlot == EWeaponSlot::Secondary && Weapon2_Secondary)
		{
			bHasWeaponEquipped = true;
			OwnerCharacter->bHasWeaponEquipped = true;
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Weapon 2 is available and Weapon Equiping from Secondary slot  !"));

			PlayerEquippedWeapon = Weapon2_Secondary;
			PlayerEquippedWeapon->SetHidden(false);
			PlayerEquippedWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), CharacterWeaponSocketName);
			
		}
		if(AM_Idle_Equip_Primary)
        {
        			
        			GetOwnerCharacter()->PlayAnimMontage(AM_Idle_Equip_Primary,1.0f);
        }
		
	
	}
	OnWeaponEquipDelegate.Broadcast(PlayerEquippedWeapon);
	
}

void UCoreInventorySystemComponent::UnEquipWeapon()
{
	if(!bHasWeaponEquipped)
	{
		return;
	}
	PlayerEquippedWeapon->Destroy();
	bHasWeaponEquipped =false;
	if(AM_Equip_Idle_Primary)
	{
		GetOwnerCharacter()->PlayAnimMontage(AM_Equip_Idle_Primary,1.0f);
	}
	OnWeaponEquipDelegate.Broadcast(PlayerEquippedWeapon);
}

void UCoreInventorySystemComponent::EquipWeaponFromID(AItem_Weapon* Weapon)
{

}

void UCoreInventorySystemComponent::SwapWeapon(EWeaponSlot WeaponSlotToSwapNewWeapon)
{
	if(bHasWeaponEquipped && EquippedWeaponSlot == WeaponSlotToSwapNewWeapon )
	{
		return;
	}
	if(bHasWeaponEquipped && EquippedWeaponSlot != WeaponSlotToSwapNewWeapon )
	{
		PlayerEquippedWeapon->Destroy();
		if(WeaponSlotToSwapNewWeapon == EWeaponSlot::Primary && Weapon1_Primary)
		{
			EquipWeapon(EWeaponSlot::Primary);
			
		}
		if(WeaponSlotToSwapNewWeapon == EWeaponSlot::Secondary && Weapon2_Secondary)
		{
			EquipWeapon(EWeaponSlot::Secondary);
			
		}
		if(AM_Swap_Primary)
		{
        			
			GetOwnerCharacter()->PlayAnimMontage(AM_Swap_Primary,1.0f);
		}
		
		
	}
	
}

void UCoreInventorySystemComponent::EqUnEq_Primary()
{
	if(bHasWeaponEquipped && EquippedWeaponSlot == EWeaponSlot::Primary)
	{
		UnEquipWeapon();
		bHasWeaponEquipped =false;
	}
	if(bHasWeaponEquipped && EquippedWeaponSlot != EWeaponSlot::Primary)
	{
		SwapWeapon(EWeaponSlot::Primary);
	}
}

/*
{
	if (PlayerEquippedWeapon == nullptr)
	{
		if(Weapon1_Primary == nullptr)
		{
			bWeaponShouldIdle=false;
			//GetWorld()->GetTimerManager().SetTimer(WeaponPositionTimerHandle,this,&ACoreCharacter::SetWeaponPosition,10.0,false);
	

				
			if(WeaponIDs[0] != NAME_None)
			{
				FActorSpawnParameters SpawnParam;
				SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
				FTransform WeaponSpawnTransForm;
				FVector WeaponSpawnLocation(0.0f, 0.f, 0.f);
				FRotator WeaponRotation(0.0f, 0.f, 0.f);
				//FVector SpawnLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+100);
				Weapon1_Primary = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),WeaponSpawnLocation,WeaponRotation, SpawnParam);
				//PlayerEquippedWeapon = Weapon1_Primary ;
				Weapon1_Primary->SetID(WeaponIDs[0]);
				ACoreCharacter* WeaponOwner = GetOwnerCharacter();
				Weapon1_Primary->SetOwner(WeaponOwner);
				bHasWeaponEquipped = true;
				//FName SocketName = PlayerEquippedWeapon->CharacterSocket;
				Weapon1_Primary->Init_Weapon_Item(WeaponIDs[1]);
				if(AM_Idle_Equip_Primary)
				{
					PlayAnimMontage(AM_Equip_Idle_Primary,1.0f);
				}
				Weapon1_Primary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PlayerEquippedWeapon->CharacterSocket);
				PlayerEquippedWeapon = Weapon1_Primary ;
						
			}
			return;
		}
		if(Weapon1_Primary)
		{
			if(AM_Idle_Equip_Primary)
			{
				PlayAnimMontage(AM_Equip_Idle_Primary,1.0f);
			}
			Weapon1_Primary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), Weapon1_Primary->CharacterSocket);
			PlayerEquippedWeapon = Weapon1_Primary ;
			bHasWeaponEquipped =true;
					
			return;
		}
		if (PlayerEquippedWeapon)
		{

				
			PlayerEquippedWeapon->Destroy();
			bHasWeaponEquipped = false;
			PlayerEquippedWeapon = nullptr;
			PlayAnimMontage(AM_Equip_Idle_Primary,1.0f);
			Weapon1_Primary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocket_Primary);
		}

	}
}*/
	








