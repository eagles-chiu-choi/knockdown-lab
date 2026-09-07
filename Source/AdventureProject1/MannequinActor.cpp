// Fill out your copyright notice in the Description page of Project Settings.


#include "MannequinActor.h"

// Sets default values
AMannequinActor::AMannequinActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	check(CapsuleComponent != nullptr);
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ThirdPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ThirdPersonMesh"));
	CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	check(ThirdPersonMeshComponent != nullptr);
	ThirdPersonMeshComponent->SetupAttachment(CapsuleComponent);

}

// Called when the game starts or when spawned
void AMannequinActor::BeginPlay()
{
	Super::BeginPlay();
	MyGameState = Cast<AMyGameState>(GetWorld()->GetGameState());
	if (MyGameState != nullptr)
	{
		// Set the third-person mesh.
		ThirdPersonMeshComponent->SetSkeletalMesh(ThirdPersonMesh.Get());
		// Set the animations on the third-person mesh.
		ThirdPersonMeshComponent->SetAnimInstanceClass(ThirdPersonDefaultAnim->GeneratedClass);
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AMannequinActor::RandomJump, FMath::RandRange(1.0f, 5.0f), false);
		FallenDestroy();
	}

}

// Called every frame
void AMannequinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AMannequinActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequinActor::DestoryMannequin()
{
	MyGameState->MannequinCountChange(MyGameState->GetMannequinCount() - 1);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AMannequinActor::DestroySelf, 2.0f, false);
}

void AMannequinActor::DestroySelf()
{
	this->Destroy();
}

void AMannequinActor::RandomJump()
{
	float rand = FMath::RandRange(1.0f, 5.0f);
	if (CapsuleComponent)
	{
		CapsuleComponent->SetSimulatePhysics(true);
		CapsuleComponent->SetMassOverrideInKg(NAME_None, 39.0f, true);
		CapsuleComponent->GetBodyInstance()->bLockXRotation = true;
		CapsuleComponent->GetBodyInstance()->bLockYRotation = true;
		CapsuleComponent->GetBodyInstance()->bLockZRotation = false;
		CapsuleComponent->AddImpulse(FVector(0.0f, 0.0f, 30000.0f));

	}
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AMannequinActor::RandomJump, 4.0f, false);

}


void AMannequinActor::FallenDestroy()
{
	if (this->GetActorLocation().Z <= -2000)
	{
		DestoryMannequin();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Fallen"));
	}
	else
	{
		GetWorldTimerManager().SetTimer(Falling, this, &AMannequinActor::FallenDestroy, 1.0f, false);
	}
}
