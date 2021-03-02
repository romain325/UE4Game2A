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

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(this->TakeWidget());

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true);
	

	if(!ensure(ResumeBtn != nullptr)) return;
	ResumeBtn->OnClicked.AddDynamic(this, &UInGameUI::OnResumeBtnClick);

	if (!ensure(EndBtn != nullptr)) return;
	EndBtn->OnClicked.AddDynamic(this, &UInGameUI::OnEndBtnClick);

}


void UInGameUI::OnResumeBtnClick()
{
	FInputModeGameOnly InputMode;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(false);
	Cast<AProjetVR2AHUD>(PlayerController->GetHUD())->GetPlayerStatsWidget()->AddToViewport();

	this->RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	

}

void UInGameUI::OnEndBtnClick()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->ConsoleCommand("quit");
}
