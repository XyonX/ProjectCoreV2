// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Templates/SharedPointer.h"
#include "LoadingScreenUISpawner.generated.h"

class ULoadingScreenUI;

UCLASS()
class COREGAMEMANAGER_API ALoadingScreenUISpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALoadingScreenUISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Functions
	void CalculateScreenSize();
	void ConfigureButtonStyle();
	void Receiver_OnStartButtonClicked ();
	UFUNCTION(BlueprintCallable)
	ULoadingScreenUI* SetupUI ();
	

protected:
	
	//Data
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	FSlateBrush BackgroundBrush;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	FSlateBrush StartButtonBrush;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	FSlateBrush ButtonBrush_Normal;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	FSlateBrush ButtonBrush_Hovered;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Defaults")
	FSlateBrush ButtonBrush_Pressed;

	
	TSharedPtr<FButtonStyle>ButtonStyle_Start;

	float ScreenSize_X;
	float ScreenSize_Y;
	FName MainMenuName;

	//Reference

	UPROPERTY()
	ULoadingScreenUI*LoadingScreenUI;
	
};
