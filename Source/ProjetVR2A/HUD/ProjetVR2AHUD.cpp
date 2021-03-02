// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetVR2AHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "PlayerStats.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "ProjetVR2A/Character/ProjetVR2ACharacter.h"
#include "UObject/ConstructorHelpers.h"


AProjetVR2AHUD::AProjetVR2AHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	
	// Init HealthBar Widget
	const ConstructorHelpers::FClassFinder<UUserWidget> PlayerStatsClassInfo(TEXT("/Game/FirstPerson/UI/PlayerStats"));
	PlayerStatsClass = PlayerStatsClassInfo.Class;

}


void AProjetVR2AHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
	
}

void AProjetVR2AHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerStats = CreateWidget(GetWorld()->GetFirstPlayerController(), PlayerStatsClass);
	// bind widget to lp & energy
	if (AProjetVR2ACharacter* Char = Cast<AProjetVR2ACharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()))
	{
		Cast<UPlayerStats>(PlayerStats)->GetHealthBar()->PercentDelegate.BindUFunction(Char, FName("GetHealthPercent"));
		Cast<UPlayerStats>(PlayerStats)->GetEnergyBar()->PercentDelegate.BindUFunction(Char, FName("GetEnergyPercent"));
	}
	PlayerStats->AddToViewport();
}
