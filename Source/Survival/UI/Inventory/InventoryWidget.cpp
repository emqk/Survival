// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../Interaction/ItemActor.h"

void UInventoryWidget::SelectIndex(const int& index, const EInventoryOpenType& _openType)
{
	switch (_openType)
	{
	case EInventoryOpenType::Single:
		currentlySelectedItemIndex = index;
		break;
	case EInventoryOpenType::Exchange:
		secondaryCurrentlySelectedItemIndex = index;
		break;
	case EInventoryOpenType::TradePlayerBuy:
		playerBuyCurrentlySelectedItemIndex = index;
		break;
	case EInventoryOpenType::TradePlayerSell:
		playerBuyCurrentlySelectedItemIndex = index;
		break;
	default:
		break;
	}
}

UInventoryComponent* UInventoryWidget::GetInventoryByType(const EInventoryOpenType& _openType) const
{
	switch (_openType)
	{
	case EInventoryOpenType::Single:
		return currentInventory;
		break;
	case EInventoryOpenType::Exchange:
		return secondaryInventory;
		break;
	case EInventoryOpenType::TradePlayerBuy:
		return playerBuyInventory;
		break;
	case EInventoryOpenType::TradePlayerSell:
		return playerSellInventory;
		break;
	default:
		return nullptr;
		break;
	}
}

void UInventoryWidget::CloseInventoryByType(const EInventoryOpenType& _openType)
{
	switch (_openType)
	{
	case EInventoryOpenType::Single:
		currentInventory = nullptr;
		secondaryInventory = nullptr;
		playerSellInventory = nullptr;
		playerBuyInventory = nullptr;
		break;
	case EInventoryOpenType::Exchange:
		secondaryInventory = nullptr;
		playerSellInventory = nullptr;
		playerBuyInventory = nullptr;
		break;
	case EInventoryOpenType::TradePlayerBuy:
		playerBuyInventory = nullptr;
		break;
	case EInventoryOpenType::TradePlayerSell:
		playerSellInventory = nullptr;
		break;
	default:
		break;
	}
}

EInventoryOpenType UInventoryWidget::GetInventoryOpenType() const
{
	return openType;
}

void UInventoryWidget::AgreeTrade()
{
	UWorld* world = GetWorld();
	for (const FItemInstance& currItem : playerBuyInventory->GetItems())
	{
		AItemActor* instance = world->SpawnActor<AItemActor>(currItem.data->prefab, currentInventory->GetOwner()->GetActorLocation(), FRotator(0, UKismetMathLibrary::RandomFloatInRange(0, 360), 0));	
		instance->InitItemsAfterDestroy( {currItem} );
	} 
	playerBuyInventory->RemoveAllItems();
}

void UInventoryWidget::CancelTrade()
{
	playerBuyInventory->MoveAllItems(secondaryInventory);
	playerSellInventory->MoveAllItems(currentInventory);
}

void UInventoryWidget::SelectInventoryByType(UInventoryComponent* inventory, const EInventoryOpenType& _openType)
{
	switch (_openType)
	{
	case EInventoryOpenType::Single:
		currentInventory = inventory;
		break;
	case EInventoryOpenType::Exchange:
		secondaryInventory = inventory;
		break;
	case EInventoryOpenType::TradePlayerBuy:
		playerBuyInventory = inventory;
		break;
	case EInventoryOpenType::TradePlayerSell:
		playerSellInventory = inventory;
		break;
	default:
		break;
	}
}