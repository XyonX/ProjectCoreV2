/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "Utilities/InventorySystemInterface.h"

//#include "AITestSuite/Public/AITestsCommon.h"


// Add default functionality here for any IInventorySystemInterface functions that are not pure virtual.



/*
AItem_Weapon* IInventorySystemInterface::SpawnWeapon(AItem_Weapon* Weapon)
{

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
	FTransform WeaponSpawnTransForm;
	FVector WeaponSpawnLocation(0.0f, 0.f, 0.f);
	FRotator WeaponRotation(0.0f, 0.f, 0.f);
	//FVector SpawnLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+100);
	AItem_Weapon*Weapon  =  FAITestHelpers::GetWorld()->SpawnActor<AItem_Weapon>(AItem_Base::StaticClass(),WeaponSpawnLocation,WeaponRotation, SpawnParam);

	return Weapon ;
	
}*/

   
