// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerController.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREPROJECT1_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	AMyPlayerState();
	UFUNCTION()
	void HpStateChange(float NewHpState);
	UFUNCTION(BlueprintCallable)
	float HpStateGet();
	UFUNCTION(BlueprintCallable)
	float GetHpPercent();
	UFUNCTION(BlueprintCallable)
	int32 GetRemainingBalls();
	UFUNCTION()
	void UseBall();
	UFUNCTION()
	void GetBall();
	UFUNCTION()
	void PowerUpConsume();
	UFUNCTION()
	bool GetPowerUpState();
private:
	UPROPERTY()
	float MaxHpState;
	UPROPERTY()
	float CurrentHpState;
	UPROPERTY()
	int32 RemainingBallsState;
	UPROPERTY()
	AMyPlayerController* PlayerC;
	UPROPERTY()
	bool PowerRespawn;
};
