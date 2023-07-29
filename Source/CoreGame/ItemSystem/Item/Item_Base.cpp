// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Base.h"
#include "Kismet/GameplayStatics.h"
//#include"Character/CoreCharacter.h"
//#include "../../../../../Source/CoreGame/Character/CoreCharacter.h"
#include"Components/StaticMeshComponent.h"
#include"Components/SkeletalMeshComponent.h"

// Sets default values
AItem_Base::AItem_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItem_Base::BeginPlay()
{
	Super::BeginPlay();
	//MyCharacterRef = Cast<ACoreCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	//MyControllerRef = Cast<ACorePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	
}

void AItem_Base::Init(EItemType ItemTypee, FText Namee)
{
	Name = Namee ;
	ItemType = ItemTypee;
}

int AItem_Base::GetWeight()
{
	int Weight = 0 ; 

	return  Weight ;
}

void AItem_Base::UpdateAmount(bool bAdd, bool bReduce, int Amountt)
{
	if(bAdd)
	{
		Amount +=Amountt;
		
	}
	else if(bReduce)
	{

		Amount -=Amountt;
	}
	else
	{
		Amount = Amountt;
	}
}

void AItem_Base::SetID(FName IDD)
{
	ID =IDD;
}

