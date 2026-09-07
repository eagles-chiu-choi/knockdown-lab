// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include  "Blueprint/UserWidget.h"
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (WidgetClass != nullptr)
	{
		WidgetInstance = CreateWidget<UUserWidget>(this, WidgetClass);
		if (WidgetInstance)
		{
			Result = FString::Printf(TEXT(""));
			WidgetInstance->AddToViewport();
		}

	}
}


void AMyPlayerController::GameOver()
{

	FInputModeUIOnly SwitchingtoUI;
	SwitchingtoUI.SetWidgetToFocus(WidgetInstance->TakeWidget());
	SetInputMode(SwitchingtoUI);

	Result = FString::Printf(TEXT("Game Over"));
}

void AMyPlayerController::GameWin()
{
	FInputModeUIOnly SwitchingtoUI;
	SwitchingtoUI.SetWidgetToFocus(WidgetInstance->TakeWidget());
	SetInputMode(SwitchingtoUI);

	Result = FString::Printf(TEXT("Win!"));
}

FString AMyPlayerController::GetResult()
{
	return Result;
}