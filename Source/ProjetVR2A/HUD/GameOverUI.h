// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJETVR2A_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget)) class UButton* SaveNQuit = nullptr;

	UPROPERTY(meta = (BindWidget)) class UTextBlock* PlayerScore = nullptr;

	UPROPERTY(meta = (BindWidget)) class UTextBlock* HighScore = nullptr;

	UFUNCTION()
		void ToMainMenu();	

	virtual void NativeConstruct() override;

private:
	void DisableInput();
	unsigned int GetHighestScore() const;
	unsigned int SaveHighScore(const unsigned int Score);
};
