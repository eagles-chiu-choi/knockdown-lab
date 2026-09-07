// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.h"
#include "MyGameState.h"
#include "PowerUpManagement.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPROJECT1_API APowerUpManagement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpManagement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	AMyPlayerState* PlayerState;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APickupBase> PickupBaseItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Pickup Management")
	TArray<APickupBase*> SpawnedItems;

	UFUNCTION()
	void CheckAndRespawn();

};
