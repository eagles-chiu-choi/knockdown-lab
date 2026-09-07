// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPROJECT1_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD)
	UUserWidget* WidgetInstance;

	UPROPERTY()
	FString Result;
	UFUNCTION(BlueprintCallable)
	FString GetResult();
	UFUNCTION()
	void GameOver();
	UFUNCTION()
	void GameWin();
}
;