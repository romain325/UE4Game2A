// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetVR2AGameMode.h"


#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjetVR2A/HUD/ProjetVR2AHUD.h"
#include "ProjetVR2A/Character/ProjetVR2ACharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjetVR2AGameMode::AProjetVR2AGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// Define enemy type
	static ConstructorHelpers::FClassFinder<APawn> SimpleEnemyClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/Enemies/SimpleEnemyChar"));
	SimpleEnemyClass = SimpleEnemyClassFinder.Class;

	// Define music type
	static ConstructorHelpers::FObjectFinder<USoundCue> SoundClassFinder(TEXT("/Game/music/CParabola"));
	Sounds = SoundClassFinder.Object;

	
	// use our custom HUD class
	HUDClass = AProjetVR2AHUD::StaticClass();

	BeginningEnemyCount = 25;

}

void AProjetVR2AGameMode::BeginPlay() {
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);

	InitEnemySpawnPlaces();
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AProjetVR2AGameMode::SpawnEnemy, 5.0f, true);

	for (int i = 0; i < BeginningEnemyCount; i++)
	{
		SpawnEnemy();
	}
	
	AudioComp = UGameplayStatics::SpawnSound2D(this, Sounds, 1);

}

void AProjetVR2AGameMode::SpawnEnemy()
{
	GetWorld()->SpawnActor(SimpleEnemyClass, &SimpleEnemySpawnLocations[CurrentEnemySpawnTick % SimpleEnemySpawnLocations.Num()]);
	CurrentEnemySpawnTick++;
}

void AProjetVR2AGameMode::InitEnemySpawnPlaces()
{
	SimpleEnemySpawnLocations.Add(FTransform(FVector(-2555, -6520, 1270)));
	SimpleEnemySpawnLocations.Add(FTransform(FVector(4520, 1920, 340)));
	SimpleEnemySpawnLocations.Add(FTransform(FVector(4540, 12140, 1310)));
	SimpleEnemySpawnLocations.Add(FTransform(FVector(-2850, -2030, 1300)));
}

void AProjetVR2AGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}
