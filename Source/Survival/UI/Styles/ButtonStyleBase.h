// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateTypes.h"
#include "ButtonStyleBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UButtonStyleBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FButtonStyle ButtonStyle;
};
