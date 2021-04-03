// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AGrenade::AGrenade() : AWeapon()
{
	this->ImpactDamage.Damage = 1;
	this->RadialDamage.BaseDamage = 50;
	this->RadialDamage.InnerRadius = 500.f;

	// add OnHit on Capsule Collision
	if (USceneComponent* Root = GetRootComponent())
	{
		ExplosionParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DeathParticles"));
		ExplosionParticles->SetAutoActivate(false);
		
		ExplosionParticles->SetupAttachment(Root);
		ExplosionParticles->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion"));
		ExplosionParticles->SetTemplate(ParticleAsset.Object);
	}
	
}

void AGrenade::DestroyGrenade()
{
	this->Destroy();
}

void AGrenade::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                     FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	
	ExplosionParticles->Activate();
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		RadialDamage.BaseDamage, 
		GetActorLocation(), 
		RadialDamage.InnerRadius, 
		UDamageType::StaticClass(), 
		TArray<AActor*>(), 
		this, 
		(AController*)GetOwner(), 
		true, 
		ECC_Visibility);
	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AGrenade::DestroyGrenade, 0.5f, false);
}


