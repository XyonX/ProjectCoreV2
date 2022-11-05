// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/CoreCharacter.h"
#include "Character/CoreCharacterEXTENDED.h"
#include "CoreAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class COREGAME_API UCoreAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;


public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void UpdateLocationData(float DeltaTime);
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void UpdateRotationData(float DeltaTime);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance")
	ACoreCharacterEXTENDED*CoreCharacter ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance")
	FVector WorldLocation ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance")
	FRotator WorldRotation ;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance")
	float Velocity ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance")
	bool bIsInAir;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance")
	bool bIsAccelerating ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance")
	float MovementOffset;
protected:
	
};
