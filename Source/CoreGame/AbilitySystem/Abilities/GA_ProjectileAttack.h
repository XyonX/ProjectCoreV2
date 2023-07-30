/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/CoreAbility.h"
#include "GA_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class COREGAME_API UGA_ProjectileAttack : public UCoreAbility
{
	GENERATED_BODY()

public:
	UGA_ProjectileAttack();
/*
	UPROPERTY(EditAnywhere ,Category="Attack") 
	TSubclassOf<AActor>ProjectileClass;
	UPROPERTY(EditAnywhere ,Category="Attack") 
	FName HandSocketName;
	UPROPERTY(EditAnywhere ,Category="Attack")
	float AttackDelay;
	UPROPERTY(EditAnywhere ,Category="Attack")
	UAnimMontage*AttackAnim;
	UPROPERTY(EditAnywhere ,Category="Attack")
	UParticleSystem*CastingEffect;

	UWorld*GetWorld()const override;
	
	UFUNCTION()
	void AttackDelay_Elapsed(AActor*Instigator);

	virtual void OnActivateAbility_Implementation(AActor* Instigator) override;*/
};
