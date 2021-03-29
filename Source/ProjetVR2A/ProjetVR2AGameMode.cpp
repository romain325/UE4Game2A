// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetVR2AGameMode.h"



#include "MyGameUserSettings.h"
#include "Bonus/Bonus.h"
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

	BonusClasses.Add(ConstructorHelpers::FClassFinder<ABonus>(TEXT("/Game/FirstPersonCPP/Blueprints/Bonus/EnergyBonus")).Class);
	BonusClasses.Add(ConstructorHelpers::FClassFinder<ABonus>(TEXT("/Game/FirstPersonCPP/Blueprints/Bonus/HealthBonus")).Class);
	
	// use our custom HUD class
	HUDClass = AProjetVR2AHUD::StaticClass();

	BeginningEnemyCount = 25;

	ABonus::BonusCount = 0;
}

void AProjetVR2AGameMode::BeginPlay() {
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);

	InitEnemySpawnPlaces();
	InitSpawnSpawnPlaces();
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AProjetVR2AGameMode::SpawnEnemy, 3.0f, true);
	FTimerHandle Handle1;
	GetWorldTimerManager().SetTimer(Handle1, this, &AProjetVR2AGameMode::SpawnBonus, 5.0f, true);

	for (int i = 0; i < BeginningEnemyCount; i++)
	{
		SpawnEnemy();
	}

	float Volume = 1.0;
	if(GEngine)
	{
		Volume = Cast<UMyGameUserSettings>(GEngine->GetGameUserSettings())->GetMasterVolume();
	}
	AudioComp = UGameplayStatics::SpawnSound2D(this, Sounds, Volume);
}

void AProjetVR2AGameMode::SpawnEnemy()
{
	GetWorld()->SpawnActor(SimpleEnemyClass, &SimpleEnemySpawnLocations[CurrentEnemySpawnTick % SimpleEnemySpawnLocations.Num()]);
	CurrentEnemySpawnTick++;
}

void AProjetVR2AGameMode::SpawnBonus()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("COUNT: %d"), ABonus::BonusCount));
	if(ABonus::BonusCount <= 3 && ABonus::BonusCount >= 0)
	{
		GetWorld()->SpawnActor(BonusClasses[std::rand() % BonusClasses.Num()], &BonusSpawnLocations[std::rand() % BonusSpawnLocations.Num()]);
	}
}

void AProjetVR2AGameMode::InitEnemySpawnPlaces()
{
	SimpleEnemySpawnLocations.Add(FTransform(FVector(-2555, -6520, 1270)));
	SimpleEnemySpawnLocations.Add(FTransform(FVector(4520, 1920, 340)));
	SimpleEnemySpawnLocations.Add(FTransform(FVector(4540, 12140, 1310)));
	SimpleEnemySpawnLocations.Add(FTransform(FVector(-2850, -2030, 1300)));
}

void AProjetVR2AGameMode::InitSpawnSpawnPlaces()
{
	BonusSpawnLocations.Add(FTransform(FVector(-310,-4850,270)));
	BonusSpawnLocations.Add(FTransform(FVector(-110,-2680,360)));
	BonusSpawnLocations.Add(FTransform(FVector(-2190,-6200,250)));
	BonusSpawnLocations.Add(FTransform(FVector(-4790,140,270)));
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
