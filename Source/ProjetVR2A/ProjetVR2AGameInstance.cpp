// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjetVR2AGameInstance.h"

#include "HUD/GameOverUI.h"
#include "HUD/InGameUI.h"

UProjetVR2AGameInstance::UProjetVR2AGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuClassFinder(TEXT("/Game/FirstPerson/UI/PauseMenu"));
	MenuClass = MenuClassFinder.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> GameOverClassFinder(TEXT("/Game/FirstPerson/UI/GameOverUI"));
	GameOverClass = GameOverClassFinder.Class;
}

void UProjetVR2AGameInstance::LoadInGameMenu()
{
	InGameUI = CreateWidget<UInGameUI>(this, MenuClass);
	InGameUI->AddToViewport();
}

void UProjetVR2AGameInstance::LoadGameOverMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("BEFORE CHAOS"))
	GameOverUI = CreateWidget<UGameOverUI>(this, GameOverClass);
	GameOverUI->AddToViewport();
}
