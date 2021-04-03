// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetVR2AProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AProjetVR2AProjectile::AProjetVR2AProjectile() : AWeapon()
{
	this->ImpactDamage.Damage = 5;
}

void AProjetVR2AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
    Destroy();
}