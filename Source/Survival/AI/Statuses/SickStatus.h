// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCStatus.h"
#include "SickStatus.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class USickStatus : public UNPCStatus
{
	GENERATED_BODY()
public:
	virtual void TickMe(UNPCNeeds* ownerNeeds, const float& deltaTime);

	UPROPERTY(EditDefaultsOnly)
	int someValue;
};
