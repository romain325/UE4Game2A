// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ProjetVR2AGameMode.generated.h"


UCLASS(minimalapi)
class AProjetVR2AGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjetVR2AGameMode();

	UFUNCTION(BlueprintCallable, Category = "Shooter Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};



