// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogElementData.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnAnswer);

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDialogElementData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnAnswer answerDelegates;
};
