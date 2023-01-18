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

UENUM(BlueprintType)
enum class ELocomotionType: uint8
{
	
	Strafing = 0					UMETA(DisplayName = "Strafing"),
	OrientRotaionToMovement =1		UMETA(DisplayName = "Orient Rotation To Movement"),
	FourWayMovement = 2				UMETA(DisplayName = "Four Way (LU =RU = F)"),
};
UENUM(BlueprintType)
enum class ECharacterEquipmentState: uint8
{
	
	Unarmed = 0					UMETA(DisplayName = "Unamed"),
	Armed =1		UMETA(DisplayName = "Armed"),
	Melee = 2				UMETA(DisplayName = "Melee"),
	Throwable = 0					UMETA(DisplayName = "Strafing"),
};
UENUM(BlueprintType)
enum class EAnimationSet: uint8
{
	LyraAnimation = 0					UMETA(DisplayName = "Default Lyra Animation "),
	MovementAnimSetPro =1		UMETA(DisplayName = "Movement AnimSet Pro"),
	MobilityPro = 2				UMETA(DisplayName = "MobilityPro"),
	RiflePro = 3				UMETA(DisplayName = "RiflePro"),
};

USTRUCT(BlueprintType)
struct FLocomotionModes
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite ,EditAnywhere,Category="Locomotion Modes")
	ELocomotionType UnarmedLocomotionType ;
	UPROPERTY(BlueprintReadWrite ,EditAnywhere,Category="Locomotion Modes")
	ELocomotionType ArmedLocomotionType;
	UPROPERTY(BlueprintReadWrite ,EditAnywhere,Category="Locomotion Modes")
	EAnimationSet UnarmedAnimationSet;
	UPROPERTY(BlueprintReadWrite ,EditAnywhere,Category="Locomotion Modes")
	EAnimationSet ArmedAnimationSet;
	
};
USTRUCT(BlueprintType)
struct FMaxMovementSpeed  : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Locomotion")
	float Walk;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Locomotion")
	float Jog;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Locomotion")
	float Sprint;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Locomotion")
	float ADS;
	
};
UENUM(BlueprintType)
enum class EVelocityDirection : uint8
{
	Forward = 0		UMETA(DisplayName = "Forward"),
	Backward =1		UMETA(DisplayName = "Backward"),
	Left = 2		UMETA(DisplayName = "Left"),
	Right =3		UMETA(DisplayName = "Right")
};
UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	Idle = 0		UMETA(DisplayName = "Idle"),
	Walking =1		UMETA(DisplayName = "Walk"),
	Joging = 2		UMETA(DisplayName = "Jog"),
	Sprinting = 3		UMETA(DisplayName = "SPrinting"),
	Pivoting =4		UMETA(DisplayName = "Pivoting"),
	Jumping =5		UMETA(DisplayName = "Jumping")
};

UCLASS()
class COREGAME_API ACoreCharacter : public AModularCharacter
{
	GENERATED_BODY()

	
public:
	ACoreCharacter();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
	USpringArmComponent*SpringArm ;
	
	UFUNCTION(BlueprintCallable,Category="CoreCharacter")
	ACorePlayerController* GetCorePlayerController()const;


	
	//TODO Create A Game State
	//ACorePlayerState*GetPlayerController();

	UFUNCTION(BlueprintCallable,Category="CoreCharacter")
	UCoreAbilitySystemComponent* GetCoreAbilitySystemComponent();
	UFUNCTION(BlueprintCallable,Category="Getters")
	FORCEINLINE UCoreCameraComponent*GetCameraComponent(){return CameraComponent; }


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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
	UCoreCameraComponent*CameraComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
	USpringArmComponent*SpringArmADS;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
    UCorePawnComponentExtended* PawnComponentExtended;
    UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Components")
    UCoreHealthComponent*HealthComponent;
private:

   
	
	
};
