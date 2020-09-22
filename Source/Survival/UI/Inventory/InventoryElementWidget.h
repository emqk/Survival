// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Inventory/InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "InventoryElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UInventoryElementWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInventoryComponent* myInventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int myItemIndex = -1;
};
