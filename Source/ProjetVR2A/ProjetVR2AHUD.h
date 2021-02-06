// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
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

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

