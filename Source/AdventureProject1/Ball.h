// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstPersonProjectile.h"
#include "MannequinActor.h"
#include "Ball.generated.h"

/**
 * 
 */

UCLASS()
class ADVENTUREPROJECT1_API ABall : public AFirstPersonProjectile
{
	GENERATED_BODY()

	public:
	ABall();
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	private:
	FVector Up = FVector(0.0f,0.0f,1.0f);
};
