// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
#include "ScavengeType.h"
#include "ScavengeGroup.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FScavengeGroup
{
	GENERATED_BODY()

	FScavengeGroup();
	FScavengeGroup(const ScavengeType& _scavengeType, class AScavengePoint* _scavengePoint, const TArray<AAICharacter*>& _group);


	UPROPERTY(EditAnywhere)
	ScavengeType scavengeType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AAICharacter*> group;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AScavengePoint* scavagePoint;
};
