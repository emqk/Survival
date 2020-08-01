// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Managers/CrewManager.h"
#include "Managers/UIManager.h"
#include "PlayerGameMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin = "true"))
class SURVIVAL_API APlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ACrewManager* crewManager = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AUIManager* uiManager = nullptr;
};
