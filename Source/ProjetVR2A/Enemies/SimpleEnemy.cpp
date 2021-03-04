// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleEnemy.h"

// Sets default values
ASimpleEnemy::ASimpleEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Pv = MaxPv;
}

// Called when the game starts or when spawned
void ASimpleEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

float ASimpleEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Pv = Pv - DamageAmount;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("YOU FUCKEKKER %d"));


	if(Pv < 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("YOU FUCKEKKER"));
		Destroy();
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

// Called every frame
void ASimpleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASimpleEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

