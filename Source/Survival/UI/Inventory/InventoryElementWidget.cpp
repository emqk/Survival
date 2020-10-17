// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryElementWidget.h"

bool UInventoryElementWidget::MoveItemTo(UInventoryComponent* from, UInventoryComponent* to, const int& index)
{
	const FName& itemID = from->GetItems()[index].data->itemID;
	return from->MoveItem(itemID, 1, to);
}
