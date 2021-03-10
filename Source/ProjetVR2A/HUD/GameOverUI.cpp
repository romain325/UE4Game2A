// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"

#include <string>


#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ProjetVR2A/Character/ProjetVR2ACharacter.h"


void UGameOverUI::ToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

unsigned int UGameOverUI::SaveHighScore(const unsigned int Score)
{
	unsigned int Highest = GetHighestScore();
	if(Highest < Score)
	{
		Highest = Score;
		FFileHelper::SaveStringToFile(FString::FromInt(Score), *(FPaths::ProjectDir() + "highscore.txt"));
	}

	return Highest;
}

void UGameOverUI::NativeConstruct()
{
	Super::NativeConstruct();

	DisableInput();

	const unsigned int PlayerScoreVal = Cast<AProjetVR2ACharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->GetScore();

	const unsigned int HighestScoreVal = SaveHighScore(PlayerScoreVal);

	if (!ensure(HighScore != nullptr)) return;
	HighScore->SetText(FText::AsCultureInvariant(FString::Printf(TEXT("Highest Score: %d"), HighestScoreVal)));
	
	if (!ensure(PlayerScore != nullptr)) return;
	PlayerScore->SetText(FText::AsCultureInvariant(FString::Printf(TEXT("Player Score: %d"), PlayerScoreVal)));

	if (!ensure(SaveNQuit != nullptr)) return;
	SaveNQuit->OnClicked.AddDynamic(this, &UGameOverUI::ToMainMenu);
}

void UGameOverUI::DisableInput()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(this->TakeWidget());

	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true);
}

unsigned int UGameOverUI::GetHighestScore() const
{
	FString resultStr;
	FFileHelper::LoadFileToString(resultStr, *(FPaths::ProjectDir() + "highscore.txt"));
	return FCString::Atoi(*resultStr);
}
