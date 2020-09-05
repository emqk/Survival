// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerGameInstance.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::MoveItem(const FName& itemID, const int& amount, UInventoryComponent* targetInventory)
{
	int index = GetItemIndex(itemID);
	if (index >= 0)
	{
		int availableMoveAmount = FMath::Min(items[index].amount, amount);
		targetInventory->AddItem({ items[index].data, availableMoveAmount });
		RemoveItemOfID(itemID, availableMoveAmount);
		return true;
	}

	return false;
}

void UInventoryComponent::AddItemsFromAsset(const TArray<FItemInstance>& itemsToAdd)
{
	UPlayerGameInstance* gameInstance = Cast<UPlayerGameInstance>(UGameplayStatics::GetGameInstance(this));
	for (const FItemInstance& itemAssetAmount : itemsToAdd)
	{
		AddItem({ gameInstance->itemManager->GetItemData(itemAssetAmount.data->itemID), itemAssetAmount.amount });
	}
}

void UInventoryComponent::AddItem(const FItemInstance& item)
{
	int itemIndex = GetItemIndex(item.data->itemID);
	if (itemIndex >= 0)
	{
		items[itemIndex].amount += item.amount;
	}
	else
	{
		items.Add(item);
	}

	CalculateWeight();
}

bool UInventoryComponent::RemoveItem(const int32& index)
{
	if (items.IsValidIndex(index))
	{
		items.RemoveAt(index);
		CalculateWeight();
		return true;
	}
	
	return false;
}

bool UInventoryComponent::RemoveItemOfID(const FName& itemID, const int& amount)
{
	int itemIndex = GetItemIndex(itemID);
	if (itemIndex >= 0)
	{
		items[itemIndex].amount -= amount;
		CalculateWeight(); //Refresh weight after changing amount
		if (items[itemIndex].amount <= 0)
		{
			RemoveItem(itemIndex);
		}

		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't remove item-No item of id %s in Inventory"), *itemID.ToString())
	}

	return false;
}

bool UInventoryComponent::RemoveItemOfIDMax(const FName& itemID)
{
	int itemIndex = GetItemIndex(itemID);
	if (itemIndex >= 0)
	{
		RemoveItem(itemIndex);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't remove item-No item of id %s in Inventory"), *itemID.ToString())
	}

	return false;
}

bool UInventoryComponent::HaveAmountOfItem(const FName& itemID, const int& amount) const
{
	for (const FItemInstance& currItem : items)
	{
		if (currItem.data->itemID == itemID)
		{
			return currItem.amount >= amount;
		}
	}

	return false;
}

bool UInventoryComponent::HaveAmountOfItems(const TArray<FItemInstance>& neededItems) const
{
	for (const FItemInstance& currItem : neededItems)
	{
		if (!HaveAmountOfItem(currItem.data->itemID, currItem.amount))
		{
			return false;
		}
	}

	return true;
}

int UInventoryComponent::GetAmountOfItem(const FName& itemID) const
{
	int index = GetItemIndex(itemID);
	if (index >= 0)
	{
		return items[index].amount;
	}

	return 0;
}

int UInventoryComponent::GetItemIndex(const FName& itemID) const
{
	int currIndex = 0;
	for (const FItemInstance& currItem : items)
	{
		if (currItem.data->itemID == itemID)
		{
			return currIndex;
		}
		++currIndex;
	}

	return -1;
}

const TArray<FItemInstance>& UInventoryComponent::GetItems() const
{
	return items;
}

void UInventoryComponent::CalculateWeight()
{
	currentWeight = 0;
	for (const FItemInstance& currItem : items)
	{
		currentWeight += currItem.data->weight * currItem.amount;
	}
}