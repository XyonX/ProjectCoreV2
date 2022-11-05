// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CorePlayerController.h"

#include "InputAction.h"
#include "InputMappingContext.h"
#include"InputModifiers.h"

/** Map key to action for mapping context with optional modifiers. */
static void MapKey(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key, bool bNegate = false, bool bSwizzle = false, EInputAxisSwizzle SwizzleOrder = EInputAxisSwizzle::YXZ)
{
	FEnhancedActionKeyMapping& Mapping = InputMappingContext->MapKey(InputAction, Key);
	UObject* Outer = InputMappingContext->GetOuter();

	if (bNegate)
	{
		UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(Outer);
		Mapping.Modifiers.Add(Negate);
	}

	if (bSwizzle)
	{
		UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(Outer);
		Swizzle->Order = SwizzleOrder;
		Mapping.Modifiers.Add(Swizzle);
	}
}

void ACorePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*
	// creating the oinput mapping object context
	BaseMappingContext = NewObject <UInputMappingContext>(this);

	// creating the input  action
	MovementAction = NewObject<UInputAction>(this);

	
	MovementAction->ValueType = EInputActionValueType::Axis3D;

	// WITHOUT HELPER FUNCTION
	CoreMappingContext->MapKey(MoveAction,EKeys::W);
	FEnhancedActionKeyMapping&Mapping = CoreMappingContext->MapKey(MoveAction,EKeys::S);
	UInputModifier*Negate = NewObject <UInputModifierNegate>(this);
	Mapping.Modifiers.Add(Negate);

	MapKey(BaseMappingContext, MovementAction, EKeys::W);
	MapKey(BaseMappingContext, MovementAction, EKeys::S, true);
	MapKey(BaseMappingContext, MovementAction, EKeys::A, true, true);
	MapKey(BaseMappingContext, MovementAction, EKeys::D, false, true);

	*/
}
