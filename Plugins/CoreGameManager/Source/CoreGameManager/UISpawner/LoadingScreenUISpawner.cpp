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

void ALoadingScreenUISpawner::ConfigureButtonStyle()
{


	// Create the custom button style.
	ButtonStyle_Start = MakeShared<FButtonStyle>();

	// Set the normal state appearance (background brush when the button is not interacted with).
	ButtonStyle_Start->Normal.ImageSize = FVector2D(100.0f, 50.0f); // Set the size of the background.
	ButtonStyle_Start->Normal.DrawAs = ESlateBrushDrawType::Type::Box;
	ButtonStyle_Start->Normal.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	//ButtonStyle_Start->Normal.SetResourceObject(YourBackgroundBrush);

	// Set the hovered state appearance (background brush when the mouse hovers over the button).
	ButtonStyle_Start->Hovered.ImageSize = FVector2D(110.0f, 60.0f);
		ButtonStyle_Start->Hovered.DrawAs = ESlateBrushDrawType::Type::Box;
	ButtonStyle_Start->Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	//ButtonStyle_Start->Hovered.SetResourceObject(YourHoveredBackgroundBrush);

	// Set the pressed state appearance (background brush when the button is pressed).
	ButtonStyle_Start->Pressed.ImageSize = FVector2D(90.0f, 40.0f);
	ButtonStyle_Start->Pressed.DrawAs = ESlateBrushDrawType::Type::Box;
	ButtonStyle_Start->Pressed.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
	//ButtonStyle_Start->Pressed.SetResourceObject(YourPressedBackgroundBrush);
}

void ALoadingScreenUISpawner::Receiver_OnStartButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Start button clicked"));
	//UGameplayStatics::OpenLevel(GetWorld(),MainMenuName);
}

ULoadingScreenUI* ALoadingScreenUISpawner::SetupUI()
{

	LoadingScreenUI = CreateWidget<ULoadingScreenUI>(GetWorld(), ULoadingScreenUI::StaticClass());
	LoadingScreenUI->Brush_Background= MakeShared<FSlateBrush>(BackgroundBrush);
	LoadingScreenUI->Brush_StartButton= MakeShared<FSlateBrush>(StartButtonBrush);

	//Calculate Screen Size
	CalculateScreenSize();
	

	//Setup the widgets size
	LoadingScreenUI->ScreenHeight = ScreenSize_Y;
	
	LoadingScreenUI->ScreenWidth=ScreenSize_X;

	ConfigureButtonStyle();

	LoadingScreenUI->SetButtonStyle(ButtonStyle_Start);

	//sync the changes to reflect to the UI
	LoadingScreenUI->SynchronizeProperties();

	return LoadingScreenUI;
}
