// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdventureCharacter.h"
#include "Laser.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPROJECT1_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser | Axis")
	FVector Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser | Axis")
	FVector End;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser | Axis")
	float time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser | Damage")
	float Damagepertick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser | Sound")
	USoundBase* DamageSound;
	UPROPERTY(VisibleAnywhere)
	float progress;
	UPROPERTY(VisibleAnywhere)
	bool going;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser | Mesh")
	TSoftObjectPtr<UStaticMesh> LaserMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser | Mesh")
	TObjectPtr<UStaticMeshComponent> LaserMeshComponent;
	void Move();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void IncreaseDecrease();
	UFUNCTION()
	void DamageToCharacter();
public:	
	FTimerHandle LaserTimeHandle;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
