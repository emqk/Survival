// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "ItemAssetAmountData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemAssetAmountData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemDataAsset* itemAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount;
};