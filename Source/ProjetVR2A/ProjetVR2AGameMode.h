// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Enemies/SimpleEnemy.h"
#include "Sound/SoundCue.h"

#include "ProjetVR2AGameMode.generated.h"


UCLASS(minimalapi)
class AProjetVR2AGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjetVR2AGameMode();

	UFUNCTION(BlueprintCallable, Category = "Shooter Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooter Game")
	TArray<FTransform> SimpleEnemySpawnLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooter Game")
	uint8 BeginningEnemyCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
		UAudioComponent* AudioComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
		USoundCue* Sounds;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	virtual void SpawnEnemy();

	TSubclassOf<ASimpleEnemy> SimpleEnemyClass;

	virtual void InitEnemySpawnPlaces();

private:
	uint16 CurrentEnemySpawnTick = 0;

};



