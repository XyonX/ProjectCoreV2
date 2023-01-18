// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_ProjectileAttack.h"

#include "Camera/CoreCameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CoreCharacter.h"

UGA_ProjectileAttack::UGA_ProjectileAttack()
{
	AttackDelay = 0.2f;
	HandSocketName = "Muzzlez_01";

}

UWorld* UGA_ProjectileAttack::GetWorld() const
{
	UActorComponent*Comp = Cast<UActorComponent> (GetOuter());
	if(Comp)
	{
		return Comp->GetWorld();
	}
	return nullptr;
	
}

void UGA_ProjectileAttack::AttackDelay_Elapsed(AActor* Instigator)
{
	ACoreCharacter*CoreCharatcer = Cast<ACoreCharacter>(Instigator);
	if(CoreCharatcer)
	{

		if(ensure(ProjectileClass))
		{
			FVector HandLocation  = CoreCharatcer->GetMesh()->GetSocketLocation(HandSocketName);

			FActorSpawnParameters SpawnParams ;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Instigator  = CoreCharatcer ;

			FCollisionShape Shape ;
			Shape.SetSphere(20.0f);


			// Ignore Player 
			FCollisionQueryParams QueryParams ;
			QueryParams.AddIgnoredActor( CoreCharatcer);

			// Collision Object Query Param

			FCollisionObjectQueryParams ObjectQueryParams ;
			ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
			ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
			ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

			FVector TraceStart = CoreCharatcer->GetCameraComponent()->GetComponentLocation();

			FVector TraceEND = TraceStart+(CoreCharatcer->GetControlRotation().Vector()*5000);

			FHitResult HitResult ;
			if(GetWorld()->SweepSingleByObjectType(HitResult,TraceStart,TraceEND,FQuat::Identity,ObjectQueryParams,Shape,QueryParams))
			{
				TraceEND = HitResult.ImpactPoint;
				
			}
			FRotator ProjectRotation = FRotationMatrix::MakeFromX(TraceEND-HandLocation).Rotator();
			FTransform SpawnTransform   = FTransform(ProjectRotation,HandLocation);
			GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTransform,SpawnParams);

			
			
		}
		OnEndAbility_Implementation(CoreCharatcer);
	}

	
}

void UGA_ProjectileAttack::OnActivateAbility_Implementation(AActor* Instigator)
{
	Super::OnActivateAbility_Implementation(Instigator);

	ACoreCharacter*CoreCharacter = Cast<ACoreCharacter>(Instigator);
	if(CoreCharacter)
	{
		CoreCharacter->PlayAnimMontage(AttackAnim);
		//UGameplayStatics->SpawnEmmiterAttached()

		FTimerHandle TimerHandle_AttackDelay ; 
		FTimerDelegate Delegate ;
		Delegate.BindUFunction(this,"AttackDelay_Elapsed",CoreCharacter);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay,Delegate,AttackDelay,false);
	}
	

	
}
