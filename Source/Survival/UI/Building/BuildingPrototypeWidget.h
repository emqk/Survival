// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Inventory/InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "BuildingPrototypeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UBuildingPrototypeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetupTexts(const TArray<FItemInstance>& buildRequirements, const UInventoryComponent* collectedInventory);

};
