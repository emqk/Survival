// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
#include "ScavengeType.h"
#include "ScavengeGroup.generated.h"

static bool operator==(const FScavengeGroup& lhs, const FScavengeGroup& rhs)
{
	return &lhs == &rhs;
}

/**
 * 
 */
USTRUCT(BlueprintType)
struct FScavengeGroup
{
	GENERATED_BODY()

	FScavengeGroup();
	FScavengeGroup(const ScavengeType& _scavengeType, class AScavengePoint* _scavengePoint, const TArray<AAICharacter*>& _group, const float& _timeToGoBack);

	void TickMe(const float& deltaTime);
	float GetTimeToGoBackStart() const;
	float GetTimeToGoBackLeft() const;
	bool IsTripFinished() const;
	bool IsOnTrip() const;
	void StartTrip();

	UPROPERTY(EditAnywhere)
	ScavengeType scavengeType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AAICharacter*> group;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AScavengePoint* scavagePoint;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isOnTrip;
	UPROPERTY(VisibleAnywhere)
	float timeToGoBackStart;
	UPROPERTY(EditAnywhere)
	float timeToGoBackLeft;
};
