// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NPCPersonality.generated.h"


UENUM(BlueprintType)
enum class EPersonalityCategory : uint8
{
	Social
};

/**
 * 
 */
UCLASS(BlueprintType)
class SURVIVAL_API UNPCPersonality : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UFUNCTION(BlueprintCallable)
	EPersonalityCategory GetCategory() const;
	UFUNCTION(BlueprintCallable)
	float GetSocialMultiplier() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	EPersonalityCategory category;
	UPROPERTY(EditDefaultsOnly)
	float socialMultiplier = 1.0f;
};
