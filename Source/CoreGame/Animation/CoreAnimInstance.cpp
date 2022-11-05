// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CoreAnimInstance.h"

#include "PropertyAccess.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCoreAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UCoreAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	CoreCharacter=Cast<ACoreCharacterEXTENDED>(TryGetPawnOwner());
}

void UCoreAnimInstance::UpdateAnimationProperties(float DeltaTime)
{

	if(CoreCharacter ==nullptr)
	{
		CoreCharacter=Cast<ACoreCharacterEXTENDED>(TryGetPawnOwner());
		
	}
	if(CoreCharacter)
	{
		FVector VelocityWithZ (CoreCharacter->GetVelocity());
		VelocityWithZ.Z = 0;
		Velocity = VelocityWithZ.Size();

		bIsInAir = CoreCharacter->GetCharacterMovement()->IsFalling();

		if(CoreCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size()>0)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating=false;
		}
		FRotator ControlRotation = CoreCharacter->GetPlayerController()->GetControlRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(CoreCharacter->GetVelocity());
		MovementOffset = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation,ControlRotation).Yaw;
		
		
		
	}
}

void UCoreAnimInstance::UpdateLocationData(float DeltaTime)
{
	
	FVector ActorLocation = GetOwningActor()->GetActorLocation();
	WorldLocation = ActorLocation-WorldLocation ;
	FVector DisplacementSpeed = WorldLocation/DeltaTime;
	
	
}

void UCoreAnimInstance::UpdateRotationData(float DeltaTime)
{
	FRotator ActorRotation = GetOwningActor()->GetActorRotation();
	WorldRotation = ActorRotation-WorldRotation ;
	FRotator Displacement = FRotator (WorldRotation.Pitch/DeltaTime,WorldRotation.Roll/DeltaTime,WorldRotation.Yaw/DeltaTime);
}
