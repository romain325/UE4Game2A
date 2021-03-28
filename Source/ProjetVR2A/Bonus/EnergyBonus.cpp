// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyBonus.h"

void AEnergyBonus::SetupElements()
{
	this->BonusAmount = 5;
	this->BonusActivation = &AProjetVR2ACharacter::EnergyBonus;
}
