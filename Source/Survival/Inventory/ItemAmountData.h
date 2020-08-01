// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemAmountData.generated.h"

USTRUCT(BlueprintType)
struct FItemAmountData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName itemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount;
};