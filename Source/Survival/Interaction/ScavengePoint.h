// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "ScavengePoint.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API AScavengePoint : public AInteractableBase
{
	GENERATED_BODY()
	
public:
	AScavengePoint();

	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

	virtual bool InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character) override;
};
