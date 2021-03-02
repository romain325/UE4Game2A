// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjetVR2AGameInstance.h"
#include "HUD/InGameUI.h"

UProjetVR2AGameInstance::UProjetVR2AGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuClassFinder(TEXT("/Game/FirstPerson/UI/PauseMenu"));
	MenuClass = MenuClassFinder.Class;
}

void UProjetVR2AGameInstance::LoadInGameMenu()
{
	InGameUI = CreateWidget<UInGameUI>(this, MenuClass);
	InGameUI->AddToViewport();
}
