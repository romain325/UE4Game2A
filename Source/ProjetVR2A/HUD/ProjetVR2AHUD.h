// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"

#include "PlayerStats.h"
#include "GameFramework/HUD.h"
#include "ProjetVR2AHUD.generated.h"

UCLASS()
class AProjetVR2AHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjetVR2AHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UUserWidget* GetPlayerStatsWidget() const { return PlayerStats; }

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;


	TSubclassOf<class UUserWidget> PlayerStatsClass;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UUserWidget* PlayerStats{ nullptr };

};

