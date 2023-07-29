// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem/CoreInteractionComponent.h"

//#include "ItemSystem/ItemObjects/Item_Weapon.h"
//#include "ItemSystem/PickupObjects/Pickup_Weapon.h"
//#include "Kismet/GameplayStatics.h"

/*
// Sets default values for this component's properties
UCoreInteractionComponent::UCoreInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	InteractionRange= 1000.0f;
}


// Called when the game starts
void UCoreInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor*OwnerActor  = GetOwner();
	OwnerCharacter = Cast<ACoreCharacter>(OwnerActor);
	
}


// Called every frame
void UCoreInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCoreInteractionComponent::Interact_Comp()
{
	if(!OwnerCharacter)
	{
		GetOwnerCharacter();
	}
	if(OwnerCharacter)
	{
		FVector2D ViewportSize2D;
		if(GEngine && GEngine->GameViewport)
		{
			GEngine->GameViewport->GetViewportSize(ViewportSize2D);
		}
		FVector2D CrossHairLoc(ViewportSize2D.X/2,ViewportSize2D.Y/2);
		bool bViewport3D;
		FVector ViewportLoc_3D;
		FVector ViewportDir_3D;
		FVector StartLoc_Viewport;
		FVector EndLocation_Viewport;

		bViewport3D = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this,0),CrossHairLoc,ViewportLoc_3D,ViewportDir_3D);
		StartLoc_Viewport = ViewportLoc_3D;
		EndLocation_Viewport = ViewportLoc_3D+ViewportDir_3D*InteractionRange;
		FCollisionShape Shape = FCollisionShape::MakeBox(FVector(10.0f,10.0f,10.0f));
		FHitResult HitResult ;
		TArray<FHitResult> HitResultArray ;
		FCollisionQueryParams QueryParams ;
		FCollisionResponseParams ResponceParam;
		QueryParams.AddIgnoredActor(OwnerCharacter);
		//DrawDebugBox();

		//if(GetWorld()->SweepSingleByChannel(SweepResult,StartLoc_Viewport,EndLocation_Viewport,))
		if(GetWorld()->LineTraceSingleByChannel(HitResult,StartLoc_Viewport,EndLocation_Viewport,ECC_Visibility,QueryParams))
		//if(GetWorld()->LineTraceMultiByChannel(HitResultArray,StartLoc_Viewport,EndLocation_Viewport,ECC_Visibility,QueryParams,ResponceParam))
		{
			//for(AActor*HitActor : HitResultArray.Hit)
			//DrawDebugBox(GetWorld(),HitResult.Location,FVector(1.0,1.0,1.0),FColor::Green,false,5.0f);
			DrawDebugLine(GetWorld(),StartLoc_Viewport,EndLocation_Viewport,FColor::Green,false,5.0f);
			APickup_Weapon*PickupWeapon = Cast<APickup_Weapon>(HitResult.GetActor());
			if(PickupWeapon)
			{
				if(PickupWeapon)
				{
			
					if(PickupWeapon->GetClass()->ImplementsInterface(UCoreGameplayInterface::StaticClass()))
					{
						ICoreGameplayInterface::Execute_Interact(HitResult.GetActor(),OwnerCharacter);
						//Cast<ICoreInterface>(PickupObject->Interact_Implementation(OwnerCharacter));
					
					}
			
				}
			}
		
		}
	}
	
	
}

ACoreCharacter* UCoreInteractionComponent::GetOwnerCharacter()
{
	AActor*OwnerActor  = GetOwner();
	OwnerCharacter = Cast<ACoreCharacter>(OwnerActor);
	return OwnerCharacter;
}
*/
