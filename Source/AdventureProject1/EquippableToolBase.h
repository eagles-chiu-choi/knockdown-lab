// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquippableToolBase.generated.h"

class UInputMappingContext;
class AAdventureCharacter;
class UInputAction;

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREPROJECT1_API AEquippableToolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquippableToolBase();
	// First Person animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimBlueprint> FirstPersonToolAnim;

	// Third Person animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimBlueprint> ThirdPersonToolAnim;
	// Tool Skeletal Mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> ToolMeshComponent;
	// The character holding this tool
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AAdventureCharacter> OwningCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* UseAction;
	// The input mapping context associated with this tool
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> ToolMappingContext;
	// Use the tool
	UFUNCTION()
	virtual void Use();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Mesh")
	USkeletalMesh* Empty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Mesh")
	USkeletalMesh* Ball;
	// Binds the Use function to the owning character
	UFUNCTION()
	virtual void BindInputAction(const UInputAction* ActionToBind);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
