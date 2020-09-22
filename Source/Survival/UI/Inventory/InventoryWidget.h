// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Inventory/InventoryComponent.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshMyEquipment(UInventoryComponent* inventory);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshItemInfo(UInventoryComponent* inventory);

	UFUNCTION(BlueprintCallable)
	void SelectIndex(const int& index);

protected:
	UFUNCTION(BlueprintCallable)
	void SelectInventory(UInventoryComponent* inventory);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentlySelectedItemIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* currentInventory;
};
