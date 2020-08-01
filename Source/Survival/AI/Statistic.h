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
    void ChangeByAmount(const int& _amount);

    UFUNCTION(BlueprintCallable)
    int GetAmount() const;

private:
    const int minAmount = 0;
    const int maxAmount = 100;
    int amount = 0;
};