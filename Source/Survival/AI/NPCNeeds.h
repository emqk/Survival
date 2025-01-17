// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Statistic.h"
#include "NPCNeeds.generated.h"

UENUM(BlueprintType)
enum class NeedType : uint8
{
    Hunger, Hydration, Energy, Happyness, Social, Health
};

/**
 * 
 */
UCLASS(BlueprintType)
class UNPCNeeds : public UObject
{
    GENERATED_BODY()
public:
    UNPCNeeds();
    ~UNPCNeeds();

    UFUNCTION(BlueprintCallable)
    UStatistic* GetNeedByType(NeedType type) const;

public:
   static const float socialNeedThresholdToAutoJoin;
   static const float socialNeedThresholdToAutoStart;
   
private:

    UPROPERTY()
    TMap<NeedType, UStatistic*> needs;
};