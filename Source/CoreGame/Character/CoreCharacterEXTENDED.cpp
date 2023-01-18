// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CoreCharacterEXTENDED.h"
#include "EnhancedInputComponent.h"
#include "Input/InputAction_Movement.h"
#include "InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CoreLocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/Abilities/GA_ProjectileAttack.h"
#include "LocomotionComponent.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Camera/CoreCameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractionSystem/CoreInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/CorePlayerController.h"
ACoreCharacterEXTENDED::ACoreCharacterEXTENDED():
CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this,&ThisClass::OnCreateSessionComplete))
{
	
	LocomotionComponent =CreateDefaultSubobject<ULocomotionComponent>("Locomotion Component");
	AbilitySystemComp =CreateDefaultSubobject<UCoreAbilitySystemComponent>("Ability System Comp ");
	InteractionComp = CreateDefaultSubobject<UCoreInteractionComponent>("Interaction Component");
	InventorySystemComponent = CreateDefaultSubobject<UCoreInventorySystemComponent>("Inventory Comp");
	TurnRate =1.0f;
	LookupRate = 1.0f;
	ForwardFacingInterpSpeed = 10.0f;
	bWantForwardFacingMovement=true;
	CharacterEquipmentState = ECharacterEquipmentState::Unarmed;

	AimRange = 1000;
	// codes for multiplayer
	IOnlineSubsystem*OnlineSubsystem =IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		OnlineSessionInterface =  OnlineSubsystem->GetSessionInterface();
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Red,FString::Printf(TEXT("FoundSubSystem %s"),*OnlineSubsystem->GetSubsystemName().ToString()));
		}
	}
}

void ACoreCharacterEXTENDED::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef =Cast<ACorePlayerController>( UGameplayStatics::GetPlayerController(GetWorld(),0));

	MovementDelegate.AddDynamic(this,&ACoreCharacterEXTENDED::TurnCharacterToMovementDirection);
	/*switch (DefaultMovementState)
	{
	case EDefaultMovementState::Walk :
		{
			GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed.Walk;
		}
	case EDefaultMovementState::Jog :
		{
			GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed.Jog;
		}
	case EDefaultMovementState::Sprint :
		{
			GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed.Sprint;
		}
	}*/
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed.Walk;
	
}

void ACoreCharacterEXTENDED::PawnClientRestart()
{
	Super::PawnClientRestart();
	if(ACorePlayerController*PlayerController = Cast<ACorePlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(BaseMappingContext,BaseMappingPriority);
			if(GEngine)
            			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Context Binded From character class "));	
		}
		
	}
	//LocomotionComponent->BindContextWithSubsystem();
}

void ACoreCharacterEXTENDED::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);
	FindAimLocation();
	FindLocomotionState();
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
	if(IsValid(EnhancedInputComp) )
	{

		if(MovementAction)
		{
			EnhancedInputComp->BindAction(	MovementAction,ETriggerEvent::Triggered,this,&ACoreCharacterEXTENDED::EnhancedMove);
		}
		if(LookingAction)
		{
			EnhancedInputComp->BindAction(	LookingAction,ETriggerEvent::Triggered,this,&ACoreCharacterEXTENDED::EnhancedLook);
		}
		if(JumpAction)
		{
			EnhancedInputComp->BindAction(	JumpAction,ETriggerEvent::Started,this,&ACharacter::Jump);
			EnhancedInputComp->BindAction(	JumpAction,ETriggerEvent::Completed,this,&ACharacter::StopJumping);
		}
		if(CrouchAction)
		{
			EnhancedInputComp->BindAction(	CrouchAction,ETriggerEvent::Triggered,this,&ACoreCharacterEXTENDED::Crouch_Custom);
			EnhancedInputComp->BindAction(	CrouchAction,ETriggerEvent::Completed,this,&ACoreCharacterEXTENDED::UnCrouch_Custom);
		}
		if(FireAction)
		{
			EnhancedInputComp->BindAction(	FireAction,ETriggerEvent::Started,this,&ACoreCharacterEXTENDED::PrimaryAttack);
		}
		if(InteractAction)
		{
			EnhancedInputComp->BindAction(	InteractAction,ETriggerEvent::Started,this,&ACoreCharacterEXTENDED::Interact_Character);
		}
		if(ADSAction)
		{
			EnhancedInputComp->BindAction(ADSAction,ETriggerEvent::Ongoing,this,&ACoreCharacterEXTENDED::Ads_Pressed);
			EnhancedInputComp->BindAction(ADSAction,ETriggerEvent::Completed,this,&ACoreCharacterEXTENDED::Ads_Released);
		}
		if(EquipUnEquipPrimaryWeapon)
		{
			EnhancedInputComp->BindAction(	EquipUnEquipPrimaryWeapon,ETriggerEvent::Started,this,&ACoreCharacterEXTENDED::ACoreCharacterEXTENDED::EqUnEq_Primary_Character);
		}
	}
	//LocomotionComponent->BindKeyWithFunction(PlayerInputComponent);
	
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
		if(!PlayerControllerRef)
		{
			GetPlayerController();
		}
		if(PlayerControllerRef)
		{
			// getting controller rotation and finding the forward vector from control rotation
			FRotator ControlRotation = PlayerControllerRef->GetControlRotation();
			FRotator YawRot(0.0f, ControlRotation.Yaw, 0.f);
			FVector ForwardDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
			FVector RightDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
			AddMovementInput(ForwardDirection,Value[0]);
			AddMovementInput(RightDirection,Value[1]);
			if(Value[0] == 1)
			{
				//VelocityDirection = EVelocityDirection::Forward ;
				bIsMovingForward=true;
			}
			if(Value[0] == -1)
			{
				//VelocityDirection = EVelocityDirection::Backward ;
			}
			if(Value[1] == 1)
			{
				//VelocityDirection = EVelocityDirection::Right ;
			}
			if(Value[1] == -1)
			{
				//VelocityDirection = EVelocityDirection::Left ;
			}
			bIsMovingForward=false;
			MovementDelegate.Broadcast(VelocityDirection);
			//UE_LOG(LogTemp, Warning, TEXT("%s called with Input Action Value %s (magnitude %f)"), *Value.ToString(), Value.GetMagnitude());
		}
	}
	
}

void ACoreCharacterEXTENDED::EnhancedLook(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value[1]*GetWorld()->DeltaTimeSeconds*LookupRate);
	AddControllerYawInput(Value[0]*GetWorld()->DeltaTimeSeconds*TurnRate);
}

void ACoreCharacterEXTENDED::Crouch_Custom()
{
	ACharacter::Crouch();
	bIsCrouching = true;
}

void ACoreCharacterEXTENDED::UnCrouch_Custom()
{
	ACharacter::UnCrouch();
	bIsCrouching= false ;
}


void ACoreCharacterEXTENDED::PrimaryAttack()
{
	//AbilitySystemComp->GainAbility(this,UGA_ProjectileAttack);
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Primary Attack Called!"));
}

void ACoreCharacterEXTENDED::Interact_Character()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interaction Called!"));
	InteractionComp->Interact_Comp();
	
}

void ACoreCharacterEXTENDED::EqUnEq_Primary_Character()
{
	if(InventorySystemComponent)
	{
		InventorySystemComponent->EqUnEq_Primary();
	}
}


void ACoreCharacterEXTENDED::Ads_Pressed()
{
	bWeaponShouldAim = false;
	bWeaponShouldIdle =false;
	bWantsToZoom = true ;
	bInADSMode=true;
	bAiming = true;
	CameraComponent->AttachToComponent(SpringArmADS, FAttachmentTransformRules::KeepRelativeTransform,NAME_None);
	FVector RelativeLcoation(0.0f,0.0f,0.0f);
	FRotator RelativeRotation (0.0f,0.0f,0.0f);
	FLatentActionInfo LatentInfo ;
	UKismetSystemLibrary::MoveComponentTo(CameraComponent,RelativeLcoation,RelativeRotation,true,true,AdsZoomTime,false,EMoveComponentAction::Move, LatentInfo);
}

void ACoreCharacterEXTENDED::Ads_Released()
{
	bWantsToZoom = false;
	bWeaponShouldAim = true;
	bInADSMode=false;
	bAiming =false;
	CameraComponent->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform,NAME_None);
	FVector TargetLoc (0,0,0);
	FRotator TargetRot(0,0,0);
	FLatentActionInfo LatentInfo;
	//LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(CameraComponent,TargetLoc,TargetRot,true,true,AdsZoomTime,false,EMoveComponentAction::Move,LatentInfo);
}

void ACoreCharacterEXTENDED::FindLocomotionState()
{
	if(GetCharacterMovement()->Velocity.Length()==0)
	{
		LocomotionState =ELocomotionState::Idle;
	}
	if(GetCharacterMovement()->Velocity.Length() >10)
	{
		LocomotionState = ELocomotionState::Jog;
	}
	/*FVector ActorVelDir = GetMovementComponent()->Velocity/GetMovementComponent()->Velocity.Length();
	FVector ActorAccDir = GetCharacterMovement()->GetCurrentAcceleration()  /GetCharacterMovement()->GetCurrentAcceleration() .Length();
	float Dot = FVector::DotProduct(ActorVelDir,ActorAccDir);
	if(Dot == -0.5)
	{
		LocomotionState = ELocomotionState::Pivoting;
	}*/
}

void ACoreCharacterEXTENDED::TurnCharacterToMovementDirection(EVelocityDirection VelocityDirectionn)
{
	if(bWantForwardFacingMovement)
	{
		FRotator ActorROT = GetActorRotation() ;
		//FRotationMatrix::MakeFromX(GetCharacterMovement()->Velocity);
		FRotator ControlRot = GetControlRotation();

		FRotator NewRot = FMath::RInterpTo(ActorROT,ControlRot,GetWorld()->GetDeltaSeconds(),ForwardFacingInterpSpeed);
		SetActorRotation(NewRot);
		UE_LOG(LogTemp,Warning,TEXT("Forward Facing Function Called"))
	}

	
}

// called when pressing 1 key
void ACoreCharacterEXTENDED::CreateGameSession()
{
	if(!OnlineSessionInterface.IsValid())
	{
		return;
	}
	auto ExistingSession =  OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if(ExistingSession!= nullptr)
	{
		OnlineSessionInterface->DestroySession(NAME_GameSession);
	}
	OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	TSharedPtr<FOnlineSessionSetting> SessionSetting = MakeShareable(new FOnlineSessionSetting());
	const  ULocalPlayer*LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	//OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(),NAME_GameSession,*SessionSetting);
}

void ACoreCharacterEXTENDED::OnCreateSessionComplete(FName SessionName, bool bWasSucessful)
{
	if(bWasSucessful)
	{
		
	}
	else
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Yellow,FString::Printf(TEXT("Created Session : %s"),*SessionName.ToString()));
		}
	}
}

FVector ACoreCharacterEXTENDED::FindAimLocation()
{
	
	FVector ActorFwdVector = GetActorForwardVector();
	FVector CameraFwdVector = CameraComponent->GetForwardVector();
	float Dot = FVector::DotProduct(ActorFwdVector,CameraFwdVector);
	FVector NullVec = GetActorLocation() + (ActorFwdVector*AimRange);
	if(Dot>0)
	{
		bShouldAim =true;
		FVector CameraLoc = CameraComponent->GetComponentLocation();
		AimLocation_Camera = CameraLoc+(CameraFwdVector*AimRange);
		return AimLocation_Camera;
	}
	bShouldAim =false;
	return  NullVec;
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

