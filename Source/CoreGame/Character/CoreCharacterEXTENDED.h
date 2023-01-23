// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/CoreCharacter.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "InventorySystem/CoreInventorySystemComponent.h"

#include "CoreCharacterEXTENDED.generated.h"

class ULocomotionComponent;
class UCoreInteractionComponent;
/**
 * 
 */
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementDelegate ,EVelocityDirection ,  VelocityDirection );
DECLARE_DYNAMIC_DELEGATE(FOnAdsModeDelegate);
UCLASS()
class COREGAME_API ACoreCharacterEXTENDED : public ACoreCharacter
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;
	virtual void Tick(float DeltaSeconds) override;
public:

#pragma region INPUT
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MovementAction ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* LookingAction ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* JumpAction ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* FireAction ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* InteractAction ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction*CrouchAction;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction*ADSAction;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* EquipUnEquipPrimaryWeapon ;

	
	// Context THAT CONTAINS INPUT ACTIONS CAN HAVE MORE THAN ONE 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input mapping Context")
	class UInputMappingContext*BaseMappingContext;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input mapping Context")
	int32 BaseMappingPriority = 0;

#pragma region endregion 

	ACoreCharacterEXTENDED();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
	ULocomotionComponent*LocomotionComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
	UCoreAbilitySystemComponent*AbilitySystemComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
	UCoreInteractionComponent*InteractionComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
	UCoreInventorySystemComponent*InventorySystemComponent ; 

	
	UFUNCTION(BlueprintCallable,Category="Getters")
	ULocomotionComponent*GetLocomotionComponent();
	

	ACorePlayerController*PlayerControllerRef;
	ACorePlayerController* GetPlayerController(){return PlayerControllerRef;}

	// Declaration Of Functions
	

	// MOVEMENT
	void EnhancedMove (const FInputActionValue & Value);
	void EnhancedLook (const FInputActionValue & Value);
	void Crouch_Custom();
	void UnCrouch_Custom();


	//ACTION
	void PrimaryAttack();
	void Fire_Core(AItem_Weapon*Weapon);
	void FireLineTrace();
	void Interact_Character ();
	void EqUnEq_Primary_Character();

	
	UFUNCTION()
	void Ads_Pressed();
	UFUNCTION()
	void Ads_Released();

	
	//DELEGATES
	void OnWeaponEquipFunction(AItem_Weapon*Weapon);
	void OnAdsModeFunction ();

	
	//void Move(const struct FInputActionValue & ActionValue);
	/*
	// OLD INPUT HANDELLING FUNCTIONS 
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);*/
	//void MyFirstAction(const FInputActionValue& Value);


	// Declaration Of Variable

	// bool
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Movement")
	bool bIsMovingForward;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Anim")
    bool bHasWeaponEquipped ;
    UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Anim")
    bool bIsCrouching ;
    UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Anim")
    bool bIsSprinting ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	bool bWantForwardFacingMovement;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category="ControlRIG")
	bool bShouldLookAtPickup;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bWantsToZoom ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bInADSMode;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bAiming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bWeaponShouldIdle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bWeaponShouldAim ;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="IK")
	bool bShouldAim;
	

	//Vectors
    UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category="ControlRIG")
    FVector LookAtLocation ;
	// these section is for Logic Related to Character locomotion and IK
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="IK")
	FVector AimLocation_Camera;
	//UPROPERTY()
	//FVector2d ViewPortSize2D;
	
	
	


	//STRUCT
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Animation")
	FMaxMovementSpeed DefaultMovementSpeed ;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Animation")
	FLocomotionModes LocomotionModes;

	//ENUM
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Animation")
	ELocomotionState DefaultMovementState ; 
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Animation")
	ECharacterEquipmentState CharacterEquipmentState ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Animation")
	ELocomotionState LocomotionState ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Animation")
	EVelocityDirection VelocityDirection ;

	//FLOAT
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Animation")
	float TurnRate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Animation")
	float LookupRate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float  ForwardFacingInterpSpeed  ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float AdsZoomTime ;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="IK")
	float AimRange ;

	
	//DELEGATES
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	FOnMovementDelegate MovementDelegate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	FOnAdsModeDelegate OnAdsModeDelegate ;
	
	
	
	

	// GENERAL FUNCTION
	
	void TurnCharacterToMovementDirection(EVelocityDirection VelocityDirectionn);
	UFUNCTION(BlueprintCallable)
	FVector FindAimLocation();
	void SetDefaultMovementMovementSpeed();
	void CalculateCharacterState ();
	
	
	//******** section holds code releated to online subsystem*********
	
	public:

	//pointer To the Onlie Session Interface
	IOnlineSessionPtr OnlineSessionInterface;

protected:
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();
	void OnCreateSessionComplete(FName SessionName , bool bWasSucessful);
private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate ;
	
	 
	
	 
	
};
