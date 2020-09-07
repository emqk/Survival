// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Statistic.h"
#include "UObject/NoExportTypes.h"
#include "NPCRelations.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SURVIVAL_API UNPCRelations : public UObject
{
	GENERATED_BODY()
	
public:

	UNPCRelations();

	UFUNCTION(BlueprintCallable)
	TMap<int, UStatistic*> GetRelations() const;

	UFUNCTION(BlueprintCallable)
	void ChangeRelationsWith(const int& characterID);

private:
	UPROPERTY()
	TMap<int, UStatistic*> relations;
};
