// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Character/Weapon/Weapon.h"
#include "GameFramework/Actor.h"
#include "ProjetVR2AProjectile.generated.h"

UCLASS()
class PROJETVR2A_API AProjetVR2AProjectile : public AWeapon
{
	GENERATED_BODY()

public:
	AProjetVR2AProjectile();

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};

