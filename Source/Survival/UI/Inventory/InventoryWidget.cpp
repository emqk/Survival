// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

void UInventoryWidget::SelectIndex(const int& index, const EInventoryOpenType& _openType)
{
	if (_openType == EInventoryOpenType::Single)
		currentlySelectedItemIndex = index;
	else
		secondaryCurrentlySelectedItemIndex = index;
}

UInventoryComponent* UInventoryWidget::GetInventoryByType(const EInventoryOpenType& _openType) const
{
	if (_openType == EInventoryOpenType::Single)
		return currentInventory;
	else
		return secondaryInventory;
}

void UInventoryWidget::SelectInventory(UInventoryComponent* inventory)
{
	currentInventory = inventory;
}

void UInventoryWidget::SelectSecondaryInventory(UInventoryComponent* inventory)
{
	secondaryInventory = inventory;
}
