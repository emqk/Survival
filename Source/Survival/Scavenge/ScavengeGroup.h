// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
#include "ScavengeGroup.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FScavengeGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AAICharacter*> group;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AScavengePoint* scavagePoint;
};
