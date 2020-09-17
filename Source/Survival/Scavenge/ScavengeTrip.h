// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
#include "ScavengeType.h"
#include "ScavengeTrip.generated.h"


static bool operator==(const FScavengeTrip& lhs, const FScavengeTrip& rhs)
{
	return &lhs == &rhs;
}

/**
 * 
 */
USTRUCT()
struct FScavengeTrip
{
	GENERATED_BODY()

	FScavengeTrip();
	FScavengeTrip(const TArray<AAICharacter*>& _group, class AScavengePoint* _scavengePoint, const float& _timeToGoBack, const ScavengeType& _scavengeType);

	float GetTimeToGoBackStart() const;

	UPROPERTY(EditAnywhere)
	ScavengeType scavengeType;

	UPROPERTY(EditAnywhere)
	TArray<AAICharacter*> group;
	UPROPERTY(EditAnywhere)
	class AScavengePoint* scavengePoint;
	UPROPERTY(EditAnywhere)
	float timeToGoBackLeft;

protected:
	UPROPERTY(VisibleAnywhere)
	float timeToGoBackStart;
};
