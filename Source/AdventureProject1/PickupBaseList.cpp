// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBaseList.h"

// Sets default values
APickupBaseList::APickupBaseList()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
FTimerHandle RespawnTimerHandle;
// Called when the game starts or when spawned
void APickupBaseList::BeginPlay()
{
	Super::BeginPlay();
	APickupBase* SpawnedActor = Cast<APickupBase>(GetWorld()->SpawnActor<AActor>(PickupBaseItem,SpawnLocation[0],FRotator::ZeroRotator));
	SpawnedItems.Add(SpawnedActor);
	SpawnedActor = Cast<APickupBase>(GetWorld()->SpawnActor<AActor>(PickupBaseItem, SpawnLocation[1], FRotator::ZeroRotator));
	SpawnedItems.Add(SpawnedActor);
	SpawnedActor = Cast<APickupBase>(GetWorld()->SpawnActor<AActor>(PickupBaseItem, SpawnLocation[2], FRotator::ZeroRotator));
	SpawnedItems.Add(SpawnedActor);
	SpawnedActor->Disable();
	SpawnedActor = Cast<APickupBase>(GetWorld()->SpawnActor<AActor>(PickupBaseItem, SpawnLocation[3], FRotator::ZeroRotator));
	SpawnedItems.Add(SpawnedActor);
	SpawnedActor->Disable();

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &APickupBaseList::CheckAndRespawn, 4.0f, true);

}

// Called every frame
void APickupBaseList::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APickupBaseList::CheckAndRespawn()
{
	int count = 0;
	for (APickupBase* i : SpawnedItems)
	{
		if (!(i->IsDisabled()))
		{
			count += 1;
		}
	}
	while (count < 2)
	{
		int32 RandomInt = FMath::RandRange(0, 3);
		if (SpawnedItems[RandomInt]->IsDisabled())
		{
			SpawnedItems[RandomInt]->InitializePickup();
			count += 1;
		}
	}
}
