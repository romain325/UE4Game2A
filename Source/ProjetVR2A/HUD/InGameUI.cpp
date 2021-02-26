// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


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

}


void UInGameUI::OnResumeBtnClick()
{
	FInputModeGameOnly InputMode;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(false);

	this->RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);

}
