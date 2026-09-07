// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpManagement.h"

// Sets default values
APowerUpManagement::APowerUpManagement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
FTimerHandle PowerUpTimerHandle;
// Called when the game starts or when spawned
void APowerUpManagement::BeginPlay()
{
	Super::BeginPlay();
	APickupBase* SpawnedActor = Cast<APickupBase>(GetWorld()->SpawnActor<AActor>(PickupBaseItem, SpawnLocation[0], FRotator::ZeroRotator));
	SpawnedItems.Add(SpawnedActor);
	SpawnedActor->Disable();
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerState = Cast<AMyPlayerState>(PlayerController->PlayerState);
	
	GetWorldTimerManager().SetTimer(PowerUpTimerHandle, this, &APowerUpManagement::CheckAndRespawn, 10.0f, true);
}

// Called every frame
void APowerUpManagement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUpManagement::CheckAndRespawn()
{
	if (SpawnedItems.Num() > 0)
	{
		for (APickupBase* i : SpawnedItems)
		{
			if (i->IsDisabled())
			{
				if (PlayerState->GetPowerUpState())
				{
					i->InitializePickup();
					PlayerState->PowerUpConsume();
				}
			}
		}
	}

}