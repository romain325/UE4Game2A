// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"


#include "ProjetVR2AHUD.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


class AProjetVR2AHUD;

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	DisableInput();

	if(!ensure(ResumeBtn != nullptr)) return;
	ResumeBtn->OnClicked.AddDynamic(this, &UInGameUI::OnResumeBtnClick);

	if (!ensure(EndBtn != nullptr)) return;
	EndBtn->OnClicked.AddDynamic(this, &UInGameUI::OnEndBtnClick);

}

void UInGameUI::DisableInput()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(this->TakeWidget());

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true);
}

void UInGameUI::ReactiveInput()
{
	FInputModeGameOnly InputMode;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(false);
	Cast<AProjetVR2AHUD>(PlayerController->GetHUD())->GetPlayerStatsWidget()->AddToViewport();

	this->RemoveFromParent();
}


void UInGameUI::OnResumeBtnClick()
{
	ReactiveInput();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UInGameUI::OnEndBtnClick()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->ConsoleCommand("quit");
}
