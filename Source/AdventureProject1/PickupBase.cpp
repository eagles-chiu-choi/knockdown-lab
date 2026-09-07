// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBase.h"
#include "Kismet/GameplayStatics.h"
#include "ItemDefinition.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create this pickup's mesh component
	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	check(PickupMeshComponent != nullptr);
	// Create this pickup's sphere component, then attach it to the mesh component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	check(SphereComponent != nullptr);

	// Attach the sphere component to the mesh component
	SphereComponent->SetupAttachment(PickupMeshComponent);


	// Set the sphere's collision radius
	SphereComponent->SetSphereRadius(150.f);
}

// Called when the game starts or when spawned
FTimerHandle InstantPickupTimerHandle;
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize this pickup with default values
	InitializePickup();
	GetWorldTimerManager().SetTimer(InstantPickupTimerHandle, this, &APickupBase::InstantPickupF, 1.f, false);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
*	Initializes the pickup with default values by retrieving them from the associated data table.
*/
void APickupBase::InitializePickup()
{
	PickupDataTable.LoadSynchronous();
	if (PickupDataTable && !PickupItemID.IsNone())
	{
		// Retrieve the item data associated with this pickup from the Data Table
		const FItemData* ItemDataRow = PickupDataTable->FindRow<FItemData>(PickupItemID, PickupItemID.ToString());

		UItemDefinition* TempItemDefinition = ItemDataRow->ItemBase.Get();
		// Create a copy of the item with the class type
		ReferenceItem = TempItemDefinition->CreateItemCopy();
		// Check if the mesh is currently loaded by calling IsValid().
		if (TempItemDefinition->WorldMesh.IsValid()) {
			// Set the pickup's mesh to the associated item's mesh
			PickupMeshComponent->SetStaticMesh(TempItemDefinition->WorldMesh.Get());
		}
		else {
			// If the mesh isn't loaded, load it by calling LoadSynchronous().
			UStaticMesh* WorldMesh = TempItemDefinition->WorldMesh.LoadSynchronous();
			PickupMeshComponent->SetStaticMesh(WorldMesh);
		}

		// Set the mesh to visible and collidable.
		PickupMeshComponent->SetVisibility(true);
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		// Register the Overlap Event
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnSphereBeginOverlap);
		disabled = false;
	}
}

void APickupBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it's an AdventureCharacter overlapping
	AAdventureCharacter* Character = Cast<AAdventureCharacter>(OtherActor);

	if (Character != nullptr)
	{
		// Give the item to the character
		Character->GiveItem(ReferenceItem);
		Disable();
	}
	if (bShouldRespawn)
	{
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &APickupBase::InitializePickup, RespawnTime, false);

	}

}

void APickupBase::Disable()
{
	// Unregister from the Overlap Event so it is no longer triggered
	SphereComponent->OnComponentBeginOverlap.RemoveAll(this);
	// Set this pickup to be invisible and disable collision
	PickupMeshComponent->SetVisibility(false);
	PickupMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	disabled = true;
}

/**
*	Updates this pickup whenever a property is changed.
*	@param PropertyChangedEvent - contains info about the property that was changed.
*/
void APickupBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	// Handle parent class property changes
	Super::PostEditChangeProperty(PropertyChangedEvent);
	// If a property was changed, get the name of the changed property. Otherwise use none.
	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	// Verify that the changed property exists in this class and that the PickupDataTable is valid.
	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickupBase, PickupItemID) && PickupDataTable)
	{
		// Retrieve the associated ItemData for this pickup.
		if (const FItemData* ItemDataRow = PickupDataTable->FindRow<FItemData>(PickupItemID, PickupItemID.ToString()))
		{
			UItemDefinition* TempItemDefinition = ItemDataRow->ItemBase;
			// Set the pickup's mesh to the associated item's mesh
			PickupMeshComponent->SetStaticMesh(TempItemDefinition->WorldMesh.Get());
			// Set the sphere's collision radius
			SphereComponent->SetSphereRadius(150.f);

		}
	}
}
bool APickupBase::IsDisabled()
{
	return disabled;
}

void APickupBase::InstantPickupF()
{
	if (InstantPickup)
	{
		AAdventureCharacter* Character = Cast<AAdventureCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Character != nullptr)
		{
		// Give the item to the character
		Character->GiveItem(ReferenceItem);
		Disable();
		}
	}
}