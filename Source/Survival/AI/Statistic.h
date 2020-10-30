// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Statistic.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UStatistic : public UObject
{
    GENERATED_BODY()
public:
    UStatistic();
    ~UStatistic();

    UFUNCTION(BlueprintCallable)
    void ChangeByAmount(const float& _amount);

    UFUNCTION(BlueprintCallable)
    float GetAmountNormalized() const;
    UFUNCTION(BlueprintCallable)
    float GetAmount() const;

    static const float minAmount;
    static const float maxAmount;
private:
   
    float amount = 0;
};