// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStats.generated.h"

/**
 * 
 */
UCLASS()
class PROJETVR2A_API UPlayerStats : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE class UProgressBar* GetHealthBar() { return HealthBar; }
	
	FORCEINLINE class UProgressBar* GetEnergyBar() { return EnergyBar; }

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* EnergyBar = nullptr;
};
