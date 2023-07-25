// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreenUISpawner.h"
#include "CoreUI/UI/LoadingScreenUI.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALoadingScreenUISpawner::ALoadingScreenUISpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALoadingScreenUISpawner::BeginPlay()
{
	Super::BeginPlay();
	
	LoadingScreenUI = CreateWidget<ULoadingScreenUI>(GetWorld(), ULoadingScreenUI::StaticClass());
	LoadingScreenUI->Brush_Background= MakeShared<FSlateBrush>(BackgroundBrush);
	LoadingScreenUI->Brush_StartButton= MakeShared<FSlateBrush>(StartButtonBrush);
	LoadingScreenUI->ButtonStyle_StartButton=MakeShared<FButtonStyle>(ButtonStyle_Start);

	//Calculate Screen Size
	CalculateScreenSize();

	//Setup the widgets size
	LoadingScreenUI->ScreenHeight = ScreenSize_Y;
	LoadingScreenUI->ScreenWidth=ScreenSize_X;

	//sync the changes to reflect to the UI
	LoadingScreenUI->SynchronizeProperties();

}

void ALoadingScreenUISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALoadingScreenUISpawner::CalculateScreenSize()
{
	// Get the player's viewport and extract the screen width and height.
	if (GEngine && GEngine->GameViewport)
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);

		// Set the screen width and height in the widget.
		ScreenSize_X = ViewportSize.X;
		ScreenSize_Y = ViewportSize.Y;
	}
}

void ALoadingScreenUISpawner::Receiver_OnStartButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Start button clicked"));
	//UGameplayStatics::OpenLevel(GetWorld(),MainMenuName);
}
