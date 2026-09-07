// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyPlayerController.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREPROJECT1_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState | Mannequin")
	int32 MannequinCount;

	public:
	AMyGameState();
	UFUNCTION()
	void MannequinCountChange(int32 NewMannequinCount);
	UFUNCTION()
	int32 GetMannequinCount();

	private:
	AMyPlayerController* PlayerC;
};
