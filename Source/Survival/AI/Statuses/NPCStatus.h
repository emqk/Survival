// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../NPCNeeds.h"
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
	void TickMe(UNPCNeeds* ownerNeeds, const float& deltaTime);

protected:
	UPROPERTY(EditDefaultsOnly)
	float food;
	UPROPERTY(EditDefaultsOnly)
	float hydration;
	UPROPERTY(EditDefaultsOnly)
	float energy;
	UPROPERTY(EditDefaultsOnly)
	float happyness;
	UPROPERTY(EditDefaultsOnly)
	float social;
	UPROPERTY(EditDefaultsOnly)
	float health;
};
