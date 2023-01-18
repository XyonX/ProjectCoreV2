// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_Weapon.h"
#include "Engine/DataTable.h"
#include "Components/WidgetComponent.h"
#include "InventorySystem/CoreInventorySystemComponent.h"


APickup_Weapon::APickup_Weapon()
{
	
	
}

void APickup_Weapon::BeginPlay()
{

	Super::BeginPlay();
	
}

void APickup_Weapon::Init_Pickup_Weapon(FName IDD)
{
	ID=IDD;
	//WeaponDatTable = LoadObjFromPath<UDataTable>(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	WeaponDatTable = LoadObjFromPath(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	//WeaponDatTable = LoadObjFromPath(TEXT("ShooterCore/DataTable/DT_Item_Weapon.DT_Item_Weapon"));

	//static ConstructorHelpers::FObjectFinder<UDataTable>WeaponDataTableObject(TEXT("'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	
	
	
	//static ConstructorHelpers::FObjectFinder<UDataTable>WeaponDataTableObject(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	
	if(WeaponDatTable)
	
	{

			UE_LOG(LogTemp, Warning, TEXT("Data Table Found") );
			TArray<FName> RowNames = WeaponDatTable->GetRowNames();
			FItemWeapon* WeaponItem = WeaponDatTable->FindRow<FItemWeapon>(IDD,"Context");
			if(WeaponItem)
			{
				FText EQUIP ;
				InitPickup(EItemType::Weapon,WeaponItem->Name,EQUIP,WeaponItem->StaticMesh);
			}
		
	}
	
}

void APickup_Weapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	
}

void APickup_Weapon::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnComponentEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void APickup_Weapon::SpawnAndStorWeapon(AItem_Weapon* VarToStore)
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	VarToStore =   GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),FVector(0.0f,0.0f,0.0f),FRotator(0.0f,0.0f,0.0f),SpawnParam);
}

void APickup_Weapon::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	if(bCanPickup)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("B Pickup is true in pickup weapon "));
		UCoreInventorySystemComponent*InventorySystemComp = Cast<UCoreInventorySystemComponent>( InstigatorPawn->GetComponentByClass(UCoreInventorySystemComponent::StaticClass()));
		
		if(InventorySystemComp)
		{
			FActorSpawnParameters SpawnParam;
			AItem_Weapon*Weapon  ; 
			Weapon = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),InstigatorPawn->GetActorLocation(),InstigatorPawn->GetActorRotation(),SpawnParam);
			Weapon->Init_Weapon_Item(ID);
			InventorySystemComp->Weapon1_Primary = Weapon ;
			InventorySystemComp->Weapon1_Primary->SetHidden(true);
			InventorySystemComp->EquipWeapon(EWeaponSlot::Primary) ;
			Destroy();
			InteractWidget->SetVisibility(false);
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped Char varified . Linetrace Sucessfull , Interactioion call from pickup weapon!"));
		}
		
		
		

	}
}

/*
void APickup_Weapon::Interact_Implementation(ACoreCharacter* InstigatorCharacter)
{

	if(bCanPickup)
	{
		/*
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
		FVector SpawnLoc = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+50.0f);
		AItem_Weapon*SpawnedWeapon = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),SpawnLoc,InstigatorCharacter->GetActorRotation(),SpawnParam);
		SpawnedWeapon->SetOwner(InstigatorCharacter);
		//SpawnedWeapon->SetHidden(true);
		if(SpawnedWeapon)
		{
			UE_LOG(LogTemp, Warning, TEXT("Weapon Spawned And stored as spawnedweapon") );
		}
		InstigatorCharacter->Weapon1_Primary = SpawnedWeapon ;
		
		if(InstigatorCharacter->Weapon1_Primary)
		{
			UE_LOG(LogTemp, Warning, TEXT("Weapon Stored In character as weapon1rimary ") );

		}
		InstigatorCharacter->Weapon1_Primary->SetID(ID);
		InstigatorCharacter->Weapon1_Primary->Init_Weapon_Item(ID);
		InstigatorCharacter->WeaponIDs[1] = ID;
		InstigatorCharacter->SpawnWeapon_Primary();
		InteractWidget->SetVisibility(false);
		Destroy();
		

		return;

	}
}*/


