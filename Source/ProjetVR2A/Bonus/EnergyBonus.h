// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "EnergyBonus.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJETVR2A_API AEnergyBonus : public ABonus
{
	GENERATED_BODY()

protected:
	virtual void SetupElements() override;
};
