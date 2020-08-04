// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class SURVIVAL_API UItemDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
        
public:

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName itemID;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText name;
};
