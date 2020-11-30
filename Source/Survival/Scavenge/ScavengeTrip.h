// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "../AI/AICharacter.h"
//#include "ScavengeType.h"
#include "ScavengeGroup.h"
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

	FScavengeTrip();
	FScavengeTrip(const ScavengeType& _scavengeType, class AScavengePoint* _scavengePoint, const TArray<AAICharacter*>& _group, const float& _timeToGoBack);

	float GetTimeToGoBackStart() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FScavengeGroup scavengeGroup;

	UPROPERTY(EditAnywhere)
	float timeToGoBackLeft;

protected:
	UPROPERTY(VisibleAnywhere)
	float timeToGoBackStart;
};
