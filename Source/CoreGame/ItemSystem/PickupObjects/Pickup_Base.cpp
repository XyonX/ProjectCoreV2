// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_Base.h"
#include "Components/SphereComponent.h"
#include "Character/CoreCharacter.h"
#include "DrawDebugHelpers.h"
#include "Chaos/CollisionResolution.h"
#include "Character/CoreCharacterEXTENDED.h"
#include "Components/WidgetComponent.h"
#include "InventorySystem/CoreInventorySystemComponent.h"

APickup_Base::APickup_Base()
{
	bReplicates = true ;


	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(RootSceneComp);


	// Creating Collision Sphere
	CollisionSphere=CreateDefaultSubobject<USphereComponent>(TEXT("Collision Box"));
	CollisionSphere->SetupAttachment(RootComponent);
	/*CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);*/
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this ,&APickup_Base::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this,&APickup_Base::APickup_Base::OnComponentEndOverlap);

	
	// create mesh for pickup mesh
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	// making pickup mesh root component
	PickupMesh->SetupAttachment(CollisionSphere);
	// Setting Up Pickup Mesh Collision
	PickupMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	

	// creating outline mesh 
	OutlineMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutlineMesh"));
	OutlineMesh->SetupAttachment(PickupMesh);
	OutlineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	

	OnPickupCollisionEvent.AddDynamic(this,&APickup_Base::EnableOutline);
	OnPickupCollisionEventEnd.AddDynamic(this,&APickup_Base::DisableOutline);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupInteractWidget"));
	InteractWidget->SetupAttachment(RootComponent);
}

void APickup_Base::BeginPlay()
{
	Super::BeginPlay();
	//if(GetLocalRole()==ENetRole::ROLE_Authority)
	/*
	if(HasAuthority())
	{
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Overlap);
	}*/
	


	FVector EndPoint = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z-1000);

	FHitResult HitResult ;
	FCollisionObjectQueryParams QuerryParamObject ;
	FCollisionQueryParams QuerryParam ;
	GetWorld()->LineTraceSingleByChannel(HitResult,GetActorLocation(),EndPoint,ECC_Visibility,QuerryParam);
	DrawDebugLine(GetWorld(),GetActorLocation(),EndPoint,FColor::Green,false,2.0f );
	SetActorLocation(HitResult.Location);
	
	if(InteractWidget)
	{
		InteractWidget->SetVisibility(false);
	}
}

void APickup_Base::InitPickup(EItemType ItemTypee, FText Namee, FText UI_Prefixx, UStaticMesh* StaticMeshh)
{

	Init(ItemTypee,Namee);
	UI_Prefix = UI_Prefixx;
	PickupMesh->SetStaticMesh( StaticMeshh);
}

void APickup_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bCanPickup= true;
	UE_LOG(LogTemp, Warning, TEXT("Someone Overlapped But not varified ") )
	ACoreCharacterEXTENDED*CollidedCharacter = Cast<ACoreCharacterEXTENDED>(OtherActor);
	if(CollidedCharacter)
	{
		OnPickupCollisionEvent.Broadcast(this);
		UE_LOG(LogTemp, Warning, TEXT("Character  Overlapped and varified ") )

		CollidedCharacter->bShouldLookAtPickup = true;
		CollidedCharacter->LookAtLocation = PickupMesh->GetComponentLocation();
		if(InteractWidget)
		{
			InteractWidget->SetVisibility(true);
		}

	}
	
}

void APickup_Base::OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	bCanPickup = false ;
	ACoreCharacter*CollidedCharacter = Cast<ACoreCharacter>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("Character leave the  box ") )
	if(CollidedCharacter)
	{
		OnPickupCollisionEventEnd.Broadcast(this);

		if(InteractWidget)
		{
			InteractWidget->SetVisibility(false);
		}
		
	}
	
}

void APickup_Base::Interact_Implementation(APawn*InstigatorPawn)
{
	ICoreGameplayInterface::Interact_Implementation(InstigatorPawn);
	
	

	
}

/*
void APickup_Base::InteractPure(ACoreCharacter* InstigatorCharacter)
{

	
}*/

