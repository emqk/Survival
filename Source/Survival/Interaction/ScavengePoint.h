// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Scavenge/ScavengeGroup.h"
#include "../Inventory/ItemInstance.h"
#include "PointOfInterest.h"
#include "ScavengePoint.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API AScavengePoint : public APointOfInterest
{
	GENERATED_BODY()
	
public:
	AScavengePoint();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool ContainsScavengeGroup(const FScavengeGroup& scavengeGroup);
	UFUNCTION(BlueprintCallable)
	void RemoveAndDisableGroup(const FScavengeGroup& scavengeGroup);

protected:
	virtual void OnBeginOverlap() override;
};
