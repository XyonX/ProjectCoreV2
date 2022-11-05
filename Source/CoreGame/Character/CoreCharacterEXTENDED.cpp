// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CoreCharacterEXTENDED.h"
#include "EnhancedInputComponent.h"
#include "Input/InputAction_Movement.h"
#include "InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CoreLocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "Player/CorePlayerController.h"
ACoreCharacterEXTENDED::ACoreCharacterEXTENDED()
{
	
	LocomotionComponent =CreateDefaultSubobject<ULocomotionComponent>("Locomotion Component");
	
	
}

void ACoreCharacterEXTENDED::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef =Cast<ACorePlayerController>( UGameplayStatics::GetPlayerController(GetWorld(),0));
}

void ACoreCharacterEXTENDED::PawnClientRestart()
{
	Super::PawnClientRestart();
	if(ACorePlayerController*PlayerController = Cast<ACorePlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerController->BaseMappingContext,PlayerController->BaseMappingPriority);
		}
		
		
	}
	//LocomotionComponent->BindContextWithSubsystem(PlayerControllerRef);
}

void ACoreCharacterEXTENDED::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{



    /*
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this,& ACoreCharacterEXTENDED::MoveForward );
	PlayerInputComponent->BindAxis("MoveRight", this, & ACoreCharacterEXTENDED::MoveRight);
	PlayerInputComponent->BindAxis ("Turn" , this , &ACoreCharacterEXTENDED::Turn);
	*/

	/*
	
	//Make Sure We have an  enhanced input system
	UEnhancedInputComponent* EnhancedInputComp =Cast <UEnhancedInputComponent>(PlayerInputComponent);
	const ACorePlayerController*PlayerController =Cast <ACorePlayerController>(Controller);
	if(IsValid(EnhancedInputComp) && IsValid(PlayerController))
	{
		EnhancedInputComp->BindAction(PlayerController->MovementAction,ETriggerEvent::Triggered,this,&ACoreCharacterEXTENDED::Move);
		UCoreLocalPlayer* LocalPlayer =  Cast<UCoreLocalPlayer>(PlayerController->GetLocalPlayer());
		check(LocalPlayer);
		UEnhancedInputLocalPlayerSubsystem * Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(Subsystem);
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(PlayerController->CoreMappingContext,0);
		
	}*/


	//Make Sure We have an  enhanced input system
	UEnhancedInputComponent* EnhancedInputComp =Cast <UEnhancedInputComponent>(PlayerInputComponent);
	const ACorePlayerController*PlayerController =Cast <ACorePlayerController>(Controller);
	if(IsValid(EnhancedInputComp) && IsValid(PlayerController))
	{

		if(LocomotionComponent->MovementAction)
		{
			EnhancedInputComp->BindAction(	PlayerController->MovementAction,ETriggerEvent::Triggered,this,&ACoreCharacterEXTENDED::EnhancedMove);
		}
		if(LocomotionComponent->LookingAction)
		{
			EnhancedInputComp->BindAction(	PlayerController->MovementAction,ETriggerEvent::Triggered,this,&ACoreCharacterEXTENDED::EnhancedLook);
		}
		if(LocomotionComponent->JumpAction)
		{
			EnhancedInputComp->BindAction(	PlayerController->MovementAction,ETriggerEvent::Started,this,&ACharacter::Jump);
			EnhancedInputComp->BindAction(	PlayerController->MovementAction,ETriggerEvent::Completed,this,&ACharacter::StopJumping);
		}
		
	}
	
	
}



ULocomotionComponent* ACoreCharacterEXTENDED::GetLocomotionComponent()
{
	if(LocomotionComponent)
	{
		return LocomotionComponent;
	}
	return nullptr;
}

void ACoreCharacterEXTENDED::EnhancedMove(const FInputActionValue& Value)
{

	if(Value.GetMagnitude() != 0)
	{
		AddMovementInput(GetActorForwardVector(),Value[0]);
		AddMovementInput(GetActorRightVector(),Value[1]);
		//UE_LOG(LogTemp, Warning, TEXT("%s called with Input Action Value %s (magnitude %f)"), *Value.ToString(), Value.GetMagnitude());
		
	}
	
}

void ACoreCharacterEXTENDED::EnhancedLook(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value[1]*1);
	AddControllerYawInput(Value[0]);
}

/*

void ACoreCharacterEXTENDED::Move(const FInputActionValue& ActionValue)
{

	//FVector Input = ActionValue.Get<FInputActionValue::Axis3D>();
	
 // Debug log output to confirm that the handler function is running.
    UE_LOG(LogTemp, Warning, TEXT("%s called with Input Action Value %s (magnitude %f)"), *ActionValue.ToString(), ActionValue.GetMagnitude());
    // Use the GetType() function to determine Value's type, and the [] operator with an index between 0 and 2 to access its data.
	
	
}*/
/*
void ACoreCharacterEXTENDED::MoveForward(float Value)
{
	
	if(LocomotionComponent != nullptr)
	{
		LocomotionComponent->MoveForward(Value,this);
	}
	
}

void ACoreCharacterEXTENDED::MoveRight(float Value)
{
	
	if(LocomotionComponent != nullptr)
	{
		LocomotionComponent->MoveRight(Value,this	);
	}
	
}
void ACoreCharacterEXTENDED::Turn(float Value)
{
	if(LocomotionComponent != nullptr)
	{
		LocomotionComponent->Turn(Value,this);
	}
}

void ACoreCharacterEXTENDED::LookUp(float Value)
{
	if(LocomotionComponent != nullptr)
	{
		LocomotionComponent->LookUp(Value,this);
	}
}
*/

/*
void ACoreCharacterEXTENDED::MyFirstAction(const FInputActionValue& Value)
{
	// Debug log output to confirm that the handler function is running.
	UE_LOG(LogTemp, Warning, TEXT("%s called with Input Action Value %s (magnitude %f)"), TEXT(__FUNCTION__), *Value.ToString(), Value.GetMagnitude());
	// Use the GetType() function to determine Value's type, and the [] operator with an index between 0 and 2 to access its data.
}*/

