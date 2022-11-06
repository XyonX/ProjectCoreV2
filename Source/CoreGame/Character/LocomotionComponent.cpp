// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LocomotionComponent.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Character/CoreCharacterEXTENDED.h"

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
	
	GetCorePlayerController();
	GetEXTENDEDCharacter();

	
	
}

ACorePlayerController* ULocomotionComponent::GetCorePlayerController()
{
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerControllerReference = Cast<ACorePlayerController>(PlayerController)  ;
	if (PlayerControllerReference)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PlayerController  Ref Found "));
		return  PlayerControllerReference;
	}
	else
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PlayerController Could not found Returned nullptr!"));

		
		return  nullptr;
	}
	
}

ACoreCharacterEXTENDED* ULocomotionComponent::GetEXTENDEDCharacter()
{
	AActor* MyOwner = GetOwner();
	ExtendedCharacterRef = Cast<ACoreCharacterEXTENDED>(MyOwner);
	if(ExtendedCharacterRef)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Extended Character Ref Found"));
		return  ExtendedCharacterRef;
	}
	else
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Extended Character Could not found Returned nullptr!"));

		return  nullptr;
	}
	
	
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
	if(PlayerControllerReference && ExtendedCharacterRef)
	{
		if(Value.GetMagnitude() != 0)

		{
				FRotator ControlRotation = PlayerControllerReference->GetControlRotation();
				FRotator YawRotation = FRotator(0.0f,ControlRotation.Yaw,0.0f);
				FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis((EAxis::X));
				FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis((EAxis::Y));
				ExtendedCharacterRef->AddMovementInput(ForwardVector,Value[0]);
				ExtendedCharacterRef->AddMovementInput(RightVector,Value[1]);
				UE_LOG(LogTemp, Warning, TEXT("Enhanced Move function Called") );
				//UE_LOG(LogTemp, Warning, TEXT("%s called with Input Action Value %s (magnitude %f)"), *Value.ToString(), Value.GetMagnitude());
		}
		
	}
	else
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ERROR WITH ENHANCED MOVEMENT Function"));
	}
}

void ULocomotionComponent::EnhancedLook(const FInputActionValue& Value)
{
	if(PlayerControllerReference && ExtendedCharacterRef)
	{
			ExtendedCharacterRef->AddControllerYawInput(Value[0]*TurnRate);
			ExtendedCharacterRef->AddControllerPitchInput(Value[1]*LookUpRate);
			UE_LOG(LogTemp, Warning, TEXT("Enhanced Looking Function Callewd") );
		
	}
	else
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Error In Enhanced Look Function "));	
	}
	
}

void ULocomotionComponent::BindKeyWithFunction(UInputComponent* PlayerInputComponent)
{
	if(ExtendedCharacterRef == nullptr)
	{
		GetCorePlayerController();
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Retrying Geting Extended Character ref :BindKeyWithFunction "));
	}
	
	if(ExtendedCharacterRef )
	{
		UEnhancedInputComponent*EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
		if(EIC)
		{
				EIC->BindAction(MovementAction,ETriggerEvent::Triggered,this,&ULocomotionComponent::EnhancedMove);
				EIC	->BindAction(LookingAction,ETriggerEvent::Triggered,this,&ULocomotionComponent::EnhancedLook );
				UE_LOG(LogTemp, Warning, TEXT("Movement Action Binding Done FROM SETUP INPUT") );
		}
	}
	else
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Couldnt Bind Function With Keys Error MAYBE CHARACTER REF NOT FOUND "));	
	}

}

void ULocomotionComponent::BindContextWithSubsystem()
{
	if(PlayerControllerReference == nullptr)
	{
		GetCorePlayerController();
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Retrying Geting Player Controller : BindContextWithSubsystem "));
	}
	if(PlayerControllerReference)
	{
			if(UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControllerReference->GetLocalPlayer()))
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(BaseMappingContext,BaseMappingPriority);
			}
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CONTEXT binding DONE "));	
	}
	else
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Couldnt Bind Context With Subsystem ,  Error MAYBE PlayerControllerReference NOT FOUND "));	
	}
}


