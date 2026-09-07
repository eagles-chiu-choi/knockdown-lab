// Fill out your copyright notice in the Description page of Project Settings.


#include "DartLauncher.h"
#include "../AdventureCharacter.h"
#include "../MyPlayerState.h"
#include "Kismet/KismetMathLibrary.h"

	// Called every frame
void ADartLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ADartLauncher::Use()
{
	if (PlayerState->GetRemainingBalls() > 0)
	{


		UWorld* const World = GetWorld();
		if (World != nullptr && ProjectileClass != nullptr)
		{
			FVector TargetPosition = OwningCharacter->GetCameraTargetLocation();
			// Get the correct socket to spawn the projectile from
			FVector SocketLocation = ToolMeshComponent->GetSocketLocation("Muzzle");
			FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SocketLocation, TargetPosition);
			FVector SpawnLocation = SocketLocation + UKismetMathLibrary::GetForwardVector(SpawnRotation) * 15.0;
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			// Spawn the projectile at the muzzle
			World->SpawnActor<AFirstPersonProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
		PlayerState->UseBall();
	}
}


void ADartLauncher::BindInputAction(const UInputAction* InputToBind)
{
	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(OwningCharacter->GetController()))
	{
		PlayerState = Cast<AMyPlayerState>(PlayerController->PlayerState);
		ensure(PlayerState != nullptr);

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{

			// Fire
			EnhancedInputComponent->BindAction(InputToBind, ETriggerEvent::Triggered, this, &ADartLauncher::Use);
		}
	}

}
