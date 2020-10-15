// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EquipType.h"
#include "../Interaction/DestructibleMaterialType.h"
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

    //General
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
    UTexture2D* icon;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General")
    FName itemID;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
    FText name;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
    float weight;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
    float space;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
    TSubclassOf<class AItemActor> prefab;

    //Consume
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consume")
    bool isEatable = false;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consume")
    float foodReduce = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consume")
    float thirstReduce = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consume")
    float energyBoost = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Consume")
    float happynessBoost = 0;

    //Equippable
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable")
    EDestructibleMaterialType destructMaterialType;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable")
    float destructionSpeedMultiplier = 2.0f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable")
    bool isEquippable = false;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equippable")
    EquipType equipType;
};
