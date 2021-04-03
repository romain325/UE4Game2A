// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Weapon.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

UCLASS()
class PROJETVR2A_API AGrenade : public AWeapon
{
	GENERATED_BODY()

protected:
	FRadialDamageParams RadialDamage;

	UParticleSystemComponent* ExplosionParticles;
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

	void DestroyGrenade();
	
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
