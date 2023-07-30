/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem/Item/Item_Base.h"
#include "Utilities/CoreGameplayInterface.h"
//#include "Utilities/CoreInterface.h"
#include "Pickup_Base.generated.h"

// Deligates for on overlap item with player
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickupCollisionDelegate ,AItem_Base* ,  PickupObject );

class USphereComponent;
class UWidgetComponent;


UENUM()
enum EPickupType
{

	PickableObject		UMETA(DisplayName = "PickupObjecs"), 
	WorldObject			UMETA(DisplayName = "World Object"),
};

UCLASS(BlueprintType, Blueprintable)
class COREGAME_API APickup_Base : public AItem_Base ,  public ICoreGameplayInterface
{
	GENERATED_BODY()
public:
	APickup_Base();
	virtual void Interact_Implementation(APawn*InstigatorPawn) ;
	//void Interact_Implementation(ACoreCharacter* InstigatorCharacter) override; // also  include a blueprint function
	//virtual void InteractPure(ACoreCharacter* InstigatorCharacter) override; //  c++ only function
 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	UStaticMeshComponent*PickupMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	UStaticMeshComponent*OutlineMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	USphereComponent*CollisionSphere;
	USceneComponent*RootSceneComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	FText UI_Prefix ;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void InitPickup(EItemType ItemTypee,FText Namee , FText UI_Prefixx  , UStaticMesh*StaticMeshh );
	UFUNCTION(BlueprintCallable)
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	virtual void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	 
	// declaring delegates onpickup and onpickupend collision event 

	//UPROPERTY(BlueprintAssignable, meta = (FriendlyName = "OnPickUpCollisionEventDeligate") , Category = "Pickup")
	UPROPERTY(BlueprintAssignable,Category = "Deligates")
	FPickupCollisionDelegate OnPickupCollisionEvent ;
	//UPROPERTY(BlueprintAssignable, meta = (FriendlyName = "OnPickUpCollisionEventDeligate") , Category = "Pickup")
	UPROPERTY(BlueprintAssignable,Category = "Deligates")
	FPickupCollisionDelegate OnPickupCollisionEventEnd ;
	UPROPERTY(BlueprintAssignable,Category = "Deligates")
	FOnIteractionDelegate OnInteractionEvent  ; 

	UFUNCTION(BlueprintImplementableEvent)
	void EnableOutline(AItem_Base*ItemRef);
	UFUNCTION(BlueprintImplementableEvent)
	void DisableOutline(AItem_Base*ItemRef);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	UWidgetComponent*InteractWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	EItemType PickUpObjectType ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	bool bCanPickup ;

	
};
