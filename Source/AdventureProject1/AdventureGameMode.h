// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AdventureGameMode.generated.h"

/**
 * 
 */
class AAdventureCharacter;
UCLASS()
class ADVENTUREPROJECT1_API AAdventureGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState | Player")
	AAdventureCharacter* player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState | Enemy")
	int32 EnemyCount;
};
