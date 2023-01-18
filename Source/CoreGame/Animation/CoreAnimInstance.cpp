// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CoreAnimInstance.h"

#include <string>

#include "PropertyAccess.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UCoreAnimInstance::UCoreAnimInstance()
{
	//Root_Yaw_Offset=0.f;
	//Root_Yaw_Offset_PerFrame=0.0f;
	PivotTime = -0.75 ;
	NormalTolerance = 0.0001f ; 
}

/*
void UCoreAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}*/

void UCoreAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	GetPlayerCharacter();
	GetPlayerController();
	//UpdateAnimationProperties(GetDeltaSeconds());
	
}

void UCoreAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeUpdateAnimation(DeltaSeconds);
	//UpdateAnimationProperties(DeltaSeconds);
}

void UCoreAnimInstance::UpdateAnimationProperties(float DeltaTime)
{

	
	if(CoreController==nullptr)
	{
		GetPlayerController();
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
		if(CoreController)
		{
			FRotator ControlRotation = CoreController->GetControlRotation();
			FRotator VelRotation = UKismetMathLibrary::MakeRotFromX(CoreCharacter->GetVelocity());
			FRotator AccelRotation = UKismetMathLibrary::MakeRotFromX(CoreCharacter->GetCharacterMovement()->GetCurrentAcceleration());
			MovementOffset = UKismetMathLibrary::NormalizedDeltaRotator(VelRotation,ControlRotation).Yaw;
			MovementOffsetAccel = UKismetMathLibrary::NormalizedDeltaRotator(AccelRotation,ControlRotation).Yaw;
		}
		bHasWeaponEquipped = CoreCharacter->bHasWeaponEquipped ;
		bIsCrouching=CoreCharacter->bIsCrouching;
		VelocityDirection = CoreCharacter->VelocityDirection ;

		
	
		if(-70<MovementOffsetAccel  &&  MovementOffsetAccel<70)
		{
			VelocityDirection = EVelocityDirection::Forward;
		}
		else
		{
			if(70<MovementOffsetAccel  && MovementOffsetAccel<110)
			{
				VelocityDirection = EVelocityDirection::Right;
			}
			else
			{
				if (-110<MovementOffsetAccel && MovementOffsetAccel<-70)
					VelocityDirection = EVelocityDirection::Left;
				else
				{
					VelocityDirection = EVelocityDirection::Backward;
				}
			}
			
		}
		
	}
}


void UCoreAnimInstance::TurnInPlace()
{
	if(CoreCharacter ==nullptr)
	{
		GetPlayerCharacter();
		
	}
	if(CoreController ==nullptr)
	{
		GetPlayerController();
	}
	if(CoreCharacter && CoreController )
	{
		if(CoreCharacter->GetCharacterMovement()->Velocity.Size()!=0)
		{
			Character_Yaw_LastFrame = 0.0f;
			Character_Yaw=0.0f;
			Root_Yaw_Offset_PerFrame=0.0f;
			Root_Yaw_Offset=0.0f;
		}
		if(CoreCharacter->GetCharacterMovement()->Velocity.Size()==0 )
		{
			Character_Yaw=	CoreController->GetControlRotation().Yaw;
			Root_Yaw_Offset_PerFrame = Character_Yaw-Character_Yaw_LastFrame;
			Root_Yaw_Offset+=Root_Yaw_Offset_PerFrame;
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(1,-1,FColor::Yellow,FString::Printf(TEXT("Root Yaw Offset is : %f"),Root_Yaw_Offset));
			Character_Yaw_LastFrame=Character_Yaw;
		}
	
		
	}
	
}

void UCoreAnimInstance::FindLocomotionState()
{
	if(!CoreCharacter)
	{
		GetPlayerCharacter();
	}
	if(CoreCharacter)
	{
		FVector VelocityDir = CoreCharacter->GetCharacterMovement()->Velocity;
		FVector AccelerationDirection = CoreCharacter->GetCharacterMovement()->GetCurrentAcceleration();
		VelocityDir.GetSafeNormal(NormalTolerance);
		VelocityDir.Normalize(NormalTolerance);
		AccelerationDirection.GetSafeNormal(NormalTolerance);
		AccelerationDirection.Normalize(NormalTolerance);
	
		float DotVec =  FVector::DotProduct(VelocityDir,AccelerationDirection);
		if(DotVec < PivotTime)
		{
			LocomotionState  = ELocomotionState::Pivoting ;
		}

		float VelLength  = VelocityDir.Length();
		float AccLength = AccelerationDirection.Length();
		if(CoreCharacter->GetCharacterMovement()->MaxWalkSpeed > 300.0f && VelLength> 1 && AccLength>0.5 )
		{
			LocomotionState = ELocomotionState::Joging ; 
		}
		if(CoreCharacter->GetCharacterMovement()->MaxWalkSpeed > 300.0f && VelLength> 0.5 && AccLength>0.01 )
		{
			LocomotionState = ELocomotionState::Walking ; 
		}
		
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

ACorePlayerController* UCoreAnimInstance::GetPlayerController()
{
	APlayerController*PlayerController =  UGameplayStatics::GetPlayerController(GetWorld(),0);
	CoreController=Cast<ACorePlayerController>(PlayerController);
	if(CoreController)
	{
		return CoreController;
	}
	else
	{
		return  nullptr;
	}
}

ACoreCharacter* UCoreAnimInstance::GetPlayerCharacter()
{
	CoreCharacter=Cast<ACoreCharacterEXTENDED>(TryGetPawnOwner());
	
	if(CoreCharacter)
	{
		return CoreCharacter;
		
	}
	else
	{
		return nullptr;
	}
}
