// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LocomotionComponent.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
ULocomotionComponent::ULocomotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	TurnRate = 1.5f ;
	LookUpRate = 1.5f ;
}


// Called when the game starts
void ULocomotionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* MyOwner = GetOwner();
	CoreCharacterReference = Cast<ACoreCharacter>(MyOwner);
	PlayerControllerReference =   UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
}

void ULocomotionComponent::MoveForward(float Value, ACoreCharacter* Character_Ref)
{
	if(Character_Ref)
	{
		if(Value!=0)
		{
			// checking wheathr the controller is available or not 
			if(PlayerControllerReference != nullptr)
			{
				// getting controller rotation and finding the forward vector from control rotation
				FRotator ControlRotation = PlayerControllerReference->GetControlRotation();
				FRotator YawRot(0.0f, ControlRotation.Yaw, 0.f);
				FVector ForwardDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
				UE_LOG(LogTemp, Warning, TEXT("Moving Without Freelook") );
				Character_Ref->AddMovementInput(ForwardDirection,Value);
			}
		}
			
		
	}

	
}

void ULocomotionComponent::MoveRight(float Value, ACoreCharacter* Character_Ref)
{
	if(PlayerControllerReference)
	{
		if(Character_Ref)
		{
			if(Value!=0)
			{
				// checking wheathr the controller is available or not 
				if(Character_Ref != nullptr)
				{
					// getting controller rotation and finding the forward vector from control rotation
					FRotator ControlRotation = PlayerControllerReference->GetControlRotation();
					FRotator YawRot(0.0f, ControlRotation.Yaw, 0.f);
					FVector RightDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
					UE_LOG(LogTemp, Warning, TEXT("Moving Without Freelook") );
					Character_Ref->AddMovementInput(RightDirection,Value);
				}
			}
			
		
		}
	}
	
			
}

void ULocomotionComponent::Turn(float Value, ACoreCharacter* Character_Ref)
{
	if(PlayerControllerReference)
	{
		if(Character_Ref)
		{
			
			Character_Ref->AddControllerYawInput(Value*TurnRate);
	
		}
	}

	
}

void ULocomotionComponent::LookUp(float Value, ACoreCharacter* Character_Ref)
{
	if(PlayerControllerReference)
	{
		if(Character_Ref)
		{
			
			Character_Ref->AddControllerPitchInput(Value*LookUpRate);
	
		}
	}

}

void ULocomotionComponent::EnhancedMove(const FInputActionValue& Value)
{
	if(PlayerControllerReference)
	{
		if(CoreCharacterReference)
		{
			if(Value.GetMagnitude() != 0)
			{
				FRotator ControlRotation = PlayerControllerReference->GetControlRotation();
				FRotator YawRotation = FRotator(0.0f,ControlRotation.Yaw,0.0f);
				FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis((EAxis::X));
				FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis((EAxis::Y));
				CoreCharacterReference->AddMovementInput(ForwardVector,Value[0]);
				CoreCharacterReference->AddMovementInput(RightVector,Value[1]);
				//UE_LOG(LogTemp, Warning, TEXT("%s called with Input Action Value %s (magnitude %f)"), *Value.ToString(), Value.GetMagnitude());
		
			}
			
		}
	}
}

void ULocomotionComponent::EnhancedLook(const FInputActionValue& Value)
{
	if(PlayerControllerReference)
	{
		if(CoreCharacterReference)
		{
			CoreCharacterReference->AddControllerYawInput(Value[0]*TurnRate);
			CoreCharacterReference->AddControllerPitchInput(Value[1]*LookUpRate);
			
		}
	}
	
}

void ULocomotionComponent::BindKeyWithFunction(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent*EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(CoreCharacterReference && EIC && PlayerControllerReference)
	{
		if(MovementAction)

		{
			EIC->BindAction(MovementAction,ETriggerEvent::Triggered,this,&ULocomotionComponent::EnhancedMove);
		
		}
		if(LookingAction)
		{
			EIC	->BindAction(LookingAction,ETriggerEvent::Triggered,this,&ULocomotionComponent::EnhancedLook );
		}
	}

}

void ULocomotionComponent::BindContextWithSubsystem()
{
	if(PlayerControllerReference)
	{
		if(ACorePlayerController*PlayerController = Cast<ACorePlayerController>(PlayerControllerReference))
		{
			if(UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(BaseMappingContext,BaseMappingPriority);
			}
		}
	}
}


