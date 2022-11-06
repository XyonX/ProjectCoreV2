// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "LocomotionComponent.h"
#include "Character/CoreCharacter.h"
#include "CoreCharacterEXTENDED.generated.h"

/**
 * 
 */
UCLASS()
class COREGAME_API ACoreCharacterEXTENDED : public ACoreCharacter
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;
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

	
	// Context THAT CONTAINS INPUT ACTIONS CAN HAVE MORE THAN ONE 
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input mapping Context")
	class UInputMappingContext*BaseMappingContext;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input mapping Context")
	int32 BaseMappingPriority = 0;

#pragma region endregion 

	ACoreCharacterEXTENDED();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	ULocomotionComponent*LocomotionComponent;

	
	UFUNCTION(BlueprintCallable,Category="Getters")
	ULocomotionComponent*GetLocomotionComponent();

	ACorePlayerController*PlayerControllerRef;
	ACorePlayerController* GetPlayerController(){return PlayerControllerRef;}


	void EnhancedMove (const FInputActionValue & Value);
	void EnhancedLook (const FInputActionValue & Value);

	//void Move(const struct FInputActionValue & ActionValue);

	/*
	// OLD INPUT HANDELLING FUNCTIONS 
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Turn(float Value);
	void LookUp(float Value);*/
	
	//void MyFirstAction(const FInputActionValue& Value);
	
	
};
