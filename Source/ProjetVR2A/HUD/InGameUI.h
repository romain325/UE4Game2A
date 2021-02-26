// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJETVR2A_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:	
	UPROPERTY(meta = (BindWidget)) class UButton* ResumeBtn = nullptr;


	UPROPERTY(meta = (BindWidget)) class UButton* EndBtn = nullptr;

	UFUNCTION()
	void OnResumeBtnClick();

	UFUNCTION()
	void OnEndBtnClick();
	
	virtual void NativeConstruct() override;
	
};
