// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCNeeds.h"
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
	void SetFullName(const FName& newName, const FName& newSurname);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName name = "None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName surname = "None";

	UPROPERTY()
	UNPCNeeds* myNeeds = nullptr;
};