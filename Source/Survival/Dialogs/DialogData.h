// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogElementData.h"
#include "DialogData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDialogData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDialogElementData> dialogElements;
};
