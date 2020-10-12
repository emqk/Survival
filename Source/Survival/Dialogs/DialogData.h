// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogElementData.h"
#include "Engine/DataTable.h"
#include "DialogData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDialogData
{
	GENERATED_BODY()

	FDialogData() : timeToAnswer(0), dialogTable(nullptr)
	{
	}

	FDialogData(float _time, UDataTable* _table) : timeToAnswer(_time), dialogTable(_table)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float timeToAnswer = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* dialogTable = nullptr;
};
