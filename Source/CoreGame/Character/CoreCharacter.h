// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreHealthComponent.h"
#include "ModularCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CorePlayerController.h"
#include "CoreCharacter.generated.h"

class UCoreController;
class UCoreAbilitySystemComponent;
class UCorePawnComponentExtended;
class UCoreHealthComponent ;
class UCoreCameraComponent ;


UCLASS()
class COREGAME_API ACoreCharacter : public AModularCharacter
{
	GENERATED_BODY()

	
public:
	ACoreCharacter();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	USpringArmComponent*SpringArm ;
	
	UFUNCTION(BlueprintCallable,Category="CoreCharacter")
	ACorePlayerController* GetCorePlayerController()const;

	//TODO Create A Game State
	//ACorePlayerState*GetPlayerController();

	UFUNCTION(BlueprintCallable,Category="CoreCharacter")
	UCoreAbilitySystemComponent* GetCoreAbilitySystemComponent();

protected:

	// when ability sysetm component is available then we we want to call this function
	virtual void OnAbilitySystemInitialized();
	virtual void OnAbilitySystemUninitialized();


	// Begins the death sequence for the character (disables collision, disables movement, etc...)
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	void DisableMovementAndCollision();
	void DestroyDueToDeath();
	void UninitAndDestroy();

	// Called when the death sequence for the character has completed
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnDeathFinished"))
	void K2_OnDeathFinished();
	
private:

    UCoreCameraComponent*CameraComponent;
	UCorePawnComponentExtended* PawnComponentExtended;
	UCoreHealthComponent*HealthComponent;
	
	
};
