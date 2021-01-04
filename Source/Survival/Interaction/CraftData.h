// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Inventory/ItemInstance.h"
#include "CraftData.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class SURVIVAL_API UCraftData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UFUNCTION(BlueprintCallable)
	TArray<FItemInstance> GetCraftRequirements() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemInstance itemToCraft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FItemInstance> craftRequirements;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float craftWorkAmount;
};
