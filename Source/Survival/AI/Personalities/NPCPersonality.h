// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NPCPersonality.generated.h"


UENUM(BlueprintType)
enum class EPersonalityCategory : uint8
{
	Social, Happyness
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
	UFUNCTION(BlueprintCallable)
	float GetHappynessMultiplier() const;
	UFUNCTION(BlueprintCallable)
	FText GetPersonalityDisplayText() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	FText personalityDisplayText;
	UPROPERTY(EditDefaultsOnly)
	EPersonalityCategory category;
	UPROPERTY(EditDefaultsOnly)
	float socialMultiplier = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float happynessMultiplier = 0.0f;
};
