// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleEnemy.h"

#include "Components/CapsuleComponent.h"
#include "ProjetVR2A/Character/ProjetVR2ACharacter.h"

// Sets default values
ASimpleEnemy::ASimpleEnemy()
{
	Pv = MaxPv;
	LastAttack = FDateTime::Now();

	// add OnHit on Capsule Collision
	if(UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->OnComponentHit.AddDynamic(this, &ASimpleEnemy::OnHit);

		DeathParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DeathParticles"));
		DeathParticles->AttachTo(Capsule);
		DeathParticles->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion"));
		DeathParticles->SetTemplate(ParticleAsset.Object);
		
	}
}

// Called when the game starts or when spawned
void ASimpleEnemy::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add(FName("TakeDamage"));

}

float ASimpleEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Pv = Pv - DamageAmount;

	if(Pv < 0)
	{
		OnDeath();
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ASimpleEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor == nullptr) || (OtherActor == this)) return;

	if (OtherActor->ActorHasTag("Player") && FDateTime::Now().GetTicks() - LastAttack.GetTicks() > 10e6)
	{
		// Damage class specs not use bc we don't actually need further information
		FPointDamageEvent DamageEvent;
		DamageEvent.Damage = 5;

		OtherActor->TakeDamage(DamageEvent.Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
		LastAttack = FDateTime::Now();
	}
	
}

void ASimpleEnemy::OnDeath()
{
	Cast<AProjetVR2ACharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->OnKillEnemy(this, this->KillScore, this->EnergyBonus);
	DeathParticles->Activate();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ASimpleEnemy::DestroyEnemy, 0.5f, false);
}

void ASimpleEnemy::DestroyEnemy()
{
	this->Destroy();
}


// Called every frame
void ASimpleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimpleEnemy::TryAttackPlayer()
{
	if(AProjetVR2ACharacter* Player = Cast<AProjetVR2ACharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()))
	{
		if(Player->GetDistanceTo(this) < 150)
		{
			const FHitResult emptyHitResult;
			this->OnHit(nullptr, Player, nullptr, Player->GetActorLocation(), emptyHitResult);
		}
	}

}



