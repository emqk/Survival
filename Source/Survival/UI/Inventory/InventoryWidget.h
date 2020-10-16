// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Inventory/InventoryComponent.h"
#include "InventoryOpenType.h"
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
	void OpenInventoryWidget(UInventoryComponent* inventory, const EInventoryOpenType& _openType);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshMyEquipment(UInventoryComponent* inventory);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshItemInfo(UInventoryComponent* inventory);

	UFUNCTION(BlueprintCallable)
	void SelectIndex(const int& index, const EInventoryOpenType& _openType);

	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryByType(const EInventoryOpenType& _openType) const;
	UFUNCTION(BlueprintCallable)
	void CloseInventoryByType(const EInventoryOpenType& _openType);
	UFUNCTION(BlueprintCallable)
	EInventoryOpenType GetInventoryOpenType() const;

protected:
	UFUNCTION(BlueprintCallable)
	void SelectInventory(UInventoryComponent* inventory);
	UFUNCTION(BlueprintCallable)
	void SelectSecondaryInventory(UInventoryComponent* inventory);

	//Primary
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int currentlySelectedItemIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* currentInventory;
	//Secondary
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* secondaryInventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int secondaryCurrentlySelectedItemIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EInventoryOpenType openType;
};
