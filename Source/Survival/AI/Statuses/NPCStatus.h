// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NPCStatus.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SURVIVAL_API UNPCStatus : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UFUNCTION()
	virtual void TickMe();
};
