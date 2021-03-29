// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"


#include "Components/CapsuleComponent.h"
#include "ProjetVR2A/Character/ProjetVR2ACharacter.h"

int ABonus::BonusCount = 0;

ABonus::ABonus()
{
	BonusCount++;
}

void ABonus::BeginPlay()
{
	Super::BeginPlay();
	this->SetupElements();
	if (UCapsuleComponent* capsule = Cast<UCapsuleComponent>(GetRootComponent()))
	{
		capsule->OnComponentBeginOverlap.AddDynamic(this, &ABonus::OnHit);
	}
}


void ABonus::SetupElements() {}

void ABonus::OnActivated()
{
	ABonus::BonusCount--;
	const bool dest = this->Destroy();
}

void ABonus::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                   int val, bool val2, const FHitResult& Hit)
{

	if ((OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr)) return;
	
	if (OtherActor->ActorHasTag("Player"))
	{
		if(AProjetVR2ACharacter* player = Cast<AProjetVR2ACharacter>(OtherActor))
		{
			if (this->BonusActivation)
			{
				(player->*BonusActivation)(this->BonusAmount);
			}
			this->OnActivated();
		}
	}
}

