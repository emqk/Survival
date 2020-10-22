// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogElementData.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "DialogData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UDialogData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float timeToAnswer = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText text;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* dialogTable = nullptr;
};
