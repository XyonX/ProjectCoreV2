/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
//#include "Character/CoreCharacter.h"
#include "Components/ActorComponent.h"
#include "CoreInteractionComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COREGAME_API UCoreInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoreInteractionComponent(){};
/*
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Interact_Comp();
	ACoreCharacter * OwnerCharacter ;
	float InteractionRange ;
	ACoreCharacter*GetOwnerCharacter();*/

		
};
