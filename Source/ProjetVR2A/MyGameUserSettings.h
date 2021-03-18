// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "MyGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJETVR2A_API UMyGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	FORCEINLINE float GetMasterVolume() const { return MasterVolume; };
	FORCEINLINE void SetMasterVolume(float Volume) { this->MasterVolume = Volume; };

	
protected:
	UPROPERTY(config)
		float MasterVolume;
};
