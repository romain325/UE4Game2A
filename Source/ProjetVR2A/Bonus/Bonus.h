// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjetVR2A/Character/ProjetVR2ACharacter.h"

#include "Bonus.generated.h"

UCLASS(Abstract)
class PROJETVR2A_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus();

	static int BonusCount;

protected:
	
	AProjetVR2ACharacter::FBonusFunction BonusActivation = nullptr;
	float BonusAmount;

	virtual void BeginPlay() override;
	virtual void SetupElements();
	virtual void OnActivated();
	
public:	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int val, bool val2, const FHitResult& Hit);

};
