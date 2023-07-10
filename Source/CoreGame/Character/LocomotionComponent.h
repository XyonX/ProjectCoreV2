// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreCharacter.h"
//#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "LocomotionComponent.generated.h"

class ACoreCharacterEXTENDED;
//UCLASS(ClassGroup=Movement, BlueprintType,meta=(BlueprintSpawnableComponent))
UCLASS(BlueprintType)
class COREGAME_API ULocomotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULocomotionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	
private:
	

public:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Locomotion Component")
	ACoreCharacterEXTENDED* ExtendedCharacterRef;
	ACorePlayerController * PlayerControllerReference;
	ACorePlayerController*GetCorePlayerController();
	ACoreCharacterEXTENDED*GetEXTENDEDCharacter();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float TurnRate ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float LookUpRate ;
/*
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
	int32 BaseMappingPriority = 0;*/
	
	
public:

	// LEGACY BINDING FUNCTIONS

	UFUNCTION(BlueprintCallable ,Category="Movement",meta=(DeprecatedFunction))
	void MoveForward (float Value , ACoreCharacter* Character_Ref);
	UFUNCTION(BlueprintCallable ,Category="Movement")
	void MoveRight (float Value,ACoreCharacter* Character_Ref) ;
	UFUNCTION(BlueprintCallable ,Category="Movement")
	void Turn (float Value,ACoreCharacter* Character_Ref) ;
	UFUNCTION(BlueprintCallable ,Category="Movement")
	void LookUp(float Value,ACoreCharacter* Character_Ref);


	// NEW Functions With Enhanced Input Support

	//UFUNCTION()
	//void EnhancedMove (const FInputActionValue & Value);
	//UFUNCTION()
	//void EnhancedLook (const FInputActionValue & Value);

	//void BindKeyWithFunction(UInputComponent* PlayerInputComponent);
	//void BindContextWithSubsystem();

	

	

	

	
	
	
		
};
