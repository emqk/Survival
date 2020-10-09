// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCNeeds.h"
#include "NPCRelations.h"
#include "Statuses/NPCStatuses.h"
#include "Engine/DataAsset.h"
#include "NPCData.generated.h"

UCLASS(BlueprintType)
class UNPCData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UNPCData();
	~UNPCData();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UFUNCTION(BlueprintCallable)
	FName GetFullName() const;
	UFUNCTION(BlueprintCallable)
	void SetFullName(const FName& newName, const FName& newSurname);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name = "None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName surname = "None";
};