// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBonus.h"

void AHealthBonus::SetupElements()
{
	this->BonusAmount = 2;
	this->BonusActivation = &AProjetVR2ACharacter::HealthBonus;
}
