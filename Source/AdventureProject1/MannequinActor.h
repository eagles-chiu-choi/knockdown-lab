// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyGameState.h"
#include "Components/CapsuleComponent.h"
#include "MannequinActor.generated.h"

UCLASS(Blueprintable)
class ADVENTUREPROJECT1_API AMannequinActor : public APawn
{
	GENERATED_BODY()

public:
	// Mesh Asset Reference
	AMannequinActor();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Mesh)
	TSoftObjectPtr<USkeletalMesh> ThirdPersonMesh;
	// Instance of the third-person mesh
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> ThirdPersonMeshComponent;

	// Third Person animations
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Animation)
	UAnimBlueprint* ThirdPersonDefaultAnim;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = State)
	AMyGameState* MyGameState;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DestoryMannequin();
	void DestroySelf();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void RandomJump();
	void FallenDestroy();
private:
	FTimerHandle RespawnTimerHandle;
	FTimerHandle Falling;
};
