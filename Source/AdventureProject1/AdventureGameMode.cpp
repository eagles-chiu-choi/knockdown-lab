// Fill out your copyright notice in the Description page of Project Settings.

#include "AdventureGameMode.h"
void AAdventureGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);
}