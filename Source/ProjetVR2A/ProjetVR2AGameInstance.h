// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"
#include "ProjetVR2AGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJETVR2A_API UProjetVR2AGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UInGameUI* InGameUI;

	TSubclassOf<class UUserWidget> MenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UGameOverUI* GameOverUI;

	TSubclassOf<class UUserWidget> GameOverClass;

public:
	UProjetVR2AGameInstance(const FObjectInitializer& ObjectInitializer);
	
	FORCEINLINE class UInGameUI* GetInGameUI() const { return InGameUI; }

	// Interface functions
	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	// Interface functions
	UFUNCTION(BlueprintCallable)
	void LoadGameOverMenu();

};
