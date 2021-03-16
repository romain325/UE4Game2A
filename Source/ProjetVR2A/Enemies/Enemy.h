// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class PROJETVR2A_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MaxPv = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int KillScore = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float EnergyBonus = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UParticleSystemComponent* DeathParticles;

private:
	float Pv;
	FDateTime LastAttack;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		virtual void OnDeath();

	void DestroyEnemy();

public:

	UFUNCTION(BlueprintCallable)
		void TryAttackPlayer();

};
