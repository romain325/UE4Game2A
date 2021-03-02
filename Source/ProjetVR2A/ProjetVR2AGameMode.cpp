// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetVR2AGameMode.h"
#include "ProjetVR2A/HUD/ProjetVR2AHUD.h"
#include "ProjetVR2A/Character/ProjetVR2ACharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjetVR2AGameMode::AProjetVR2AGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjetVR2AHUD::StaticClass();

}

void AProjetVR2AGameMode::BeginPlay() {
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void AProjetVR2AGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}