// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers/ItemManager.h"
#include "PlayerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UPlayerGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UItemManager* itemManager = nullptr;
};
