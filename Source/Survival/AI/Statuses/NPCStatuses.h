// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCStatus.h"
#include "UObject/NoExportTypes.h"
#include "NPCStatuses.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UNPCStatuses : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void TickStatuses(UNPCNeeds* ownerNeeds, const float& deltaTime);

	UFUNCTION(BlueprintCallable)
	void AddStatus(UNPCStatus* status);

	UFUNCTION(BlueprintCallable)
	void RemoveStatus(UNPCStatus* status);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSet<UNPCStatus*> statuses;
};
