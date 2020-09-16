// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
#include "ScavengeTrip.generated.h"


static bool operator==(const FScavengeTrip& lhs, const FScavengeTrip& rhs)
{
	return &lhs == &rhs;
}

/**
 * 
 */
USTRUCT(BlueprintType)
struct FScavengeTrip
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AAICharacter*> group;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AScavengePoint* scavagePoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float timeToGoBack;
};
