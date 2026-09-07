// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Laser.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	progress = 0.f;
	going = true;
	LaserMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMeshComponent"));
	RootComponent = LaserMeshComponent;
	Damagepertick = 0.5f;
	LaserMeshComponent->SetCollisionProfileName(FName("Laser"));
	LaserMeshComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
FTimerHandle SoundTimeHandle;
void ALaser::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(LaserTimeHandle, this, &ALaser::IncreaseDecrease, 0.01f, true);
	LaserMeshComponent->SetStaticMesh(LaserMesh.Get());
	LaserMeshComponent->SetCollisionProfileName(FName("Laser"));
	LaserMeshComponent->SetGenerateOverlapEvents(true);
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	DamageToCharacter();
}

void ALaser::Move()
{
	SetActorLocation(FMath::Lerp(Start, End, progress));
}

void ALaser::IncreaseDecrease()
{
	float increasepertime = time / 10000;
	if (going)
	{
		progress = progress + increasepertime;
	}
	else {
		progress = progress - increasepertime;
	}
	if (progress >= 0.9f)
	{
		going = false;
	}
	else if (progress <= 0.1f)
	{
		going = true;
	}
}

void ALaser::DamageToCharacter()
{
	TArray<AActor*> Actors;
	LaserMeshComponent->GetOverlappingActors(Actors);
	for (AActor* Actor : Actors)
	{

		if (AAdventureCharacter* Char = Cast<AAdventureCharacter>(Actor))
		{
			UGameplayStatics::SpawnSound2D(this, DamageSound);
			Char->DamageToCharacter(Damagepertick);
		}
	}
}
class UGameplayStatics;