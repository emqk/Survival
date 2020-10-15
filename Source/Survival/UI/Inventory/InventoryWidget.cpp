// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

void UInventoryWidget::SelectIndex(const int& index)
{
	currentlySelectedItemIndex = index;
}

void UInventoryWidget::SelectSecondaryIndex(const int& index)
{
	secondaryCurrentlySelectedItemIndex = index;
}

void UInventoryWidget::SelectInventory(UInventoryComponent* inventory)
{
	currentInventory = inventory;
}

void UInventoryWidget::SelectSecondaryInventory(UInventoryComponent* inventory)
{
	secondaryInventory = inventory;
}
