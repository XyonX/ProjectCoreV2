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

	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Movement")
	bool bIsMovingForward;

	void EnhancedMove (const FInputActionValue & Value);
	void EnhancedLook (const FInputActionValue & Value);
	void Crouch_Custom();
	void UnCrouch_Custom();

	void PrimaryAttack();
	void Interact_Character ();

	void EqUnEq_Primary_Character();

	UFUNCTION()
	void Ads_Pressed();
	UFUNCTION()
	void Ads_Released();
	void FindLocomotionState();
	//void Move(const struct FInputActionValue & ActionValue);

	/*
	// OLD INPUT HANDELLING FUNCTIONS 
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Turn(float Value);
	void LookUp(float Value);*/
	
	//void MyFirstAction(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Locomotion")
	EVelocityDirection VelocityDirection ;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Locomotion")
	float TurnRate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Locomotion")
	float LookupRate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Locomotion")
	FOnMovementDelegate MovementDelegate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Locomotion")
	bool bWantForwardFacingMovement;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Locomotion")
	float  ForwardFacingInterpSpeed  ;
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
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float AdsZoomTime ;

	
	void TurnCharacterToMovementDirection(EVelocityDirection VelocityDirectionn);
	
	//these section holds code releated to online subsystem
	
	public:

	//pointer To the Onlie Session Interface
	IOnlineSessionPtr OnlineSessionInterface;

protected:
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();
	void OnCreateSessionComplete(FName SessionName , bool bWasSucessful);
private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate ;
	
public:

	// these section is for Logic Related to Character locomotion and IK
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="IK")
	FVector AimLocation_Camera;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="IK")
	bool bShouldAim;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="IK")
	float AimRange ; 
	UFUNCTION(BlueprintCallable)
	FVector FindAimLocation();
	 
	
};
