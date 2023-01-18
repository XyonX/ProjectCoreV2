// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CoreCharacter.h"
#include"Camera/CoreCameraComponent.h"
#include "CorePawnComponentExtended.h"
#include"Camera/CoreCameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include "CoreHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACoreCharacter::ACoreCharacter()
{

	
	SpringArm =CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmADS = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring ArmADS"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArmADS->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true ;
	SpringArmADS->bUsePawnControlRotation = true ;
	CameraComponent = CreateDefaultSubobject<UCoreCameraComponent>(TEXT("Camera Component ")) ;
	check(CameraComponent)
	CameraComponent->SetupAttachment(SpringArm);
	
	PawnComponentExtended = CreateDefaultSubobject<UCorePawnComponentExtended>(TEXT("Pawn Component Extended"));

	HealthComponent =CreateDefaultSubobject<UCoreHealthComponent>(TEXT("Health Component "));

	

	// Avoid ticking characters if possible.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));  // Rotate mesh to be X forward since it is exported as Y forward.

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;

	UCapsuleComponent*CapsuleComp = GetCapsuleComponent();
	CapsuleComp->InitCapsuleSize(40.0,90.0f);

	
	check(MeshComp);
	// Rotate mesh to be X forward since it is exported as Y forward.
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	//CameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 75.0f));


	DefaultMovementState =EDefaultMovementState::Walk;
	
	BaseEyeHeight = 80.0f;
    CrouchedEyeHeight = 50.0;
	DefaultMovementSpeed.Walk = 225;
	DefaultMovementSpeed.Jog=525;
	DefaultMovementSpeed.Sprint=600;
	DefaultMovementSpeed.ADS=225;
	

	
}

void ACoreCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ACoreCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ACoreCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ACorePlayerController* ACoreCharacter::GetCorePlayerController() const
{

	return CastChecked<ACorePlayerController>(Controller);
	
}

UCoreAbilitySystemComponent* ACoreCharacter::GetCoreAbilitySystemComponent()
{
	return  PawnComponentExtended->GetAbilitySystemComponent();
}

void ACoreCharacter::OnAbilitySystemInitialized()
{
}

void ACoreCharacter::OnAbilitySystemUninitialized()
{
}

void ACoreCharacter::OnDeathStarted(AActor* OwningActor)
{
}

void ACoreCharacter::OnDeathFinished(AActor* OwningActor)
{
}

void ACoreCharacter::DisableMovementAndCollision()
{
}

void ACoreCharacter::DestroyDueToDeath()
{
}

void ACoreCharacter::UninitAndDestroy()
{
}
