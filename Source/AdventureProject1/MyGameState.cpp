// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "AdventureGameMode.h"
AMyGameState::AMyGameState()
{
    MannequinCount = 8;
}

void AMyGameState::BeginPlay()
{
    Super::BeginPlay();
    PlayerC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
}

void AMyGameState::MannequinCountChange(int32 NewMannequinCount)
{
    MannequinCount = NewMannequinCount;
    if (MannequinCount <= 0)
    {
        if (PlayerC != nullptr)
        {
            PlayerC->GameWin();
        }
    }
}

int32 AMyGameState::GetMannequinCount()
{
    return MannequinCount;
}