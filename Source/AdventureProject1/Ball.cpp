// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
ABall::ABall()
{
    PrimaryActorTick.bCanEverTick = true;
}
void ABall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
        if(AMannequinActor* Mannequin = Cast<AMannequinActor>(OtherActor)) {
            if (UCapsuleComponent* Capsule = Mannequin->FindComponentByClass<UCapsuleComponent>())
            {
                Capsule->SetSimulatePhysics(true);
                Capsule->GetBodyInstance()->bLockXRotation = false;
                Capsule->GetBodyInstance()->bLockYRotation = false;
                Capsule->GetBodyInstance()->bLockZRotation = false;
                Capsule->AddImpulseAtLocation(GetVelocity() * PhysicsForce, GetActorLocation());
                Capsule->AddImpulseAtLocation(Up * PhysicsForce, GetActorLocation());
                Mannequin->DestoryMannequin();
            }

            Destroy();
        }

	}
}