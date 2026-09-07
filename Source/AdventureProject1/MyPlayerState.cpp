// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

AMyPlayerState::AMyPlayerState()
{
	MaxHpState = 100.f;
	CurrentHpState = MaxHpState;
	PowerRespawn = true;
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerState::HpStateChange(float NewHpState)
{
	CurrentHpState = NewHpState;
	if (CurrentHpState <= 0)
	{
		PlayerC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerC->GameOver();
	}
}
float AMyPlayerState::HpStateGet()
{
	return CurrentHpState;
}
float AMyPlayerState::GetHpPercent()
{
	return CurrentHpState / MaxHpState;
}

void AMyPlayerState::GetBall()
{
	RemainingBallsState = RemainingBallsState + 1;
	PowerRespawn = true;
}
void AMyPlayerState::UseBall()
{
	RemainingBallsState = RemainingBallsState - 1;
	PowerRespawn = true;

}
int32 AMyPlayerState::GetRemainingBalls()
{
	return RemainingBallsState;
}

void AMyPlayerState::PowerUpConsume()
{
	PowerRespawn = false;
}

bool AMyPlayerState::GetPowerUpState()
{
	return PowerRespawn;
}
