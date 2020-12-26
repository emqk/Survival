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
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshTradeCosts();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetItemInfoVisibility(bool visible);

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
	void AgreeTrade();
	UFUNCTION(BlueprintCallable)
	void CancelTrade();

	UFUNCTION(BlueprintCallable)
	void SelectInventoryByType(UInventoryComponent* inventory, const EInventoryOpenType& _openType);

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
	//Player sell
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* playerSellInventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int playerSellCurrentlySelectedItemIndex;
	//Player buy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* playerBuyInventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int playerBuyCurrentlySelectedItemIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EInventoryOpenType openType;
};
