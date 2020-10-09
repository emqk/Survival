// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCNeeds.h"
#include "NPCRelations.h"
#include "NPCData.generated.h"

UCLASS(BlueprintType)
class UNPCData : public UObject
{
	GENERATED_BODY()

public:

	UNPCData();
	~UNPCData();

	UFUNCTION(BlueprintCallable)
	UNPCNeeds* GetNeeds() const;

	UFUNCTION(BlueprintCallable)
	UNPCRelations* GetRelations() const;

	UFUNCTION(BlueprintCallable)
	FName GetFullName() const;
	UFUNCTION(BlueprintCallable)
	void SetFullName(const FName& newName, const FName& newSurname);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName name = "None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName surname = "None";

	UPROPERTY(EditAnywhere)
	UStatistic* health = nullptr;

	UPROPERTY()
	UNPCNeeds* myNeeds = nullptr;

	UPROPERTY()
	UNPCRelations* myRelations = nullptr;
};