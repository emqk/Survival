// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class SURVIVAL_API UItemDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName itemID;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText name;
};
