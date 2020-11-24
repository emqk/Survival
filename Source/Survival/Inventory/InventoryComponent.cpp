// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../AI/AICharacter.h"
#include "../Interaction/ItemActor.h"
#include "../PlayerGameInstance.h"
#include "../PlayerGameMode.h"

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

	//Setup equipment slots
	const UEnum* equipTypeEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EquipType"), true);
	uint8 enumNum = equipTypeEnum->GetMaxEnumValue();
	for (uint8 i = 0; i < enumNum; i++)
	{
		equipment.Add((EquipType)i, nullptr);
	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::MoveItemByID(const FName& itemID, UInventoryComponent* targetInventory, const int& amount)
{
	int index = GetItemIndex(itemID);
	return MoveItemByIndex(index, targetInventory, amount);
}

bool UInventoryComponent::MoveItemByIndex(const int& itemIndex, UInventoryComponent* targetInventory, const int& amount)
{
	if (items.IsValidIndex(itemIndex))
	{
		int availableMoveAmount = amount < 0 ? items[itemIndex].amount : FMath::Min(items[itemIndex].amount, amount);

		if (targetInventory->AddItem({ items[itemIndex].data, availableMoveAmount }))
		{
			RemoveItem(itemIndex, availableMoveAmount);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't move item - After move, weight or space would exceed max weight/space!"))
		}
	}

	return false;
}

bool UInventoryComponent::MoveAllItems(UInventoryComponent* targetInventory)
{
	for (int i = items.Num() - 1; i >= 0; i--)
	{
		if (!MoveItemByIndex(i, targetInventory))
			return false;
	}

	return true;
}

bool UInventoryComponent::AddItemsFromAsset(const TArray<FItemInstance>& itemsToAdd)
{
	UPlayerGameInstance* gameInstance = Cast<UPlayerGameInstance>(UGameplayStatics::GetGameInstance(this));
	for (const FItemInstance& itemAssetAmount : itemsToAdd)
	{
		if(!AddItem( {gameInstance->itemManager->GetItemData(itemAssetAmount.data->itemID), itemAssetAmount.amount} ))
			return false;
	}

	return true;
}

bool UInventoryComponent::AddItem(const FItemInstance& item)
{
	int itemIndex = GetItemIndex(item.data->itemID);

	if (currentWeight + (item.data->weight * item.amount) > maxWeight
		|| currentSpace + (item.data->space * item.amount) > maxSpace)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't add item - After add, weight or space would exceed max weight/space!"))
		return false;
	}

	if (itemIndex >= 0)
	{
		items[itemIndex].amount += item.amount;
	}
	else if(item.amount > 0)
	{
		items.Add(item);
	}

	CalculateWeightAndSpace();
	RefreshUI();
	return true;
}

bool UInventoryComponent::RemoveItem(const int32& index, const int32& amount)
{
	if (items.IsValidIndex(index))
	{
		// Remove item no matter how big amount is
		if (amount < 0)
		{
			items.RemoveAt(index);
		}
		// Decrease item amount of given amount
		else
		{
			items[index].amount -= amount;
			if (items[index].amount <= 0)
			{
				items.RemoveAt(index);
			}
		}

		CalculateWeightAndSpace();
		RefreshUI();
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
		CalculateWeightAndSpace();
		RefreshUI();
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

bool UInventoryComponent::RemoveItems(const TArray<FItemInstance>& itemsToRemove)
{
	for (const FItemInstance& currItem : itemsToRemove)
	{
		if (!RemoveItemOfID(currItem.data->itemID, currItem.amount))
			return false;
	}

	return true;
}

void UInventoryComponent::RemoveAllItems()
{
	items.Empty();
	CalculateWeightAndSpace();
	RefreshUI();
}

bool UInventoryComponent::UseItemOfIndex(const int& index)
{
	if (items.IsValidIndex(index))
	{
		AAICharacter* myOwner = Cast<AAICharacter>(GetOwner());
		FItemInstance& itemToUse = items[index];
		if (myOwner)
		{
			if (itemToUse.data->isEatable)
			{
				myOwner->GetNeeds()->GetNeedByType(NeedType::Hunger)->ChangeByAmount(-itemToUse.data->foodReduce);
				myOwner->GetNeeds()->GetNeedByType(NeedType::Thirst)->ChangeByAmount(-itemToUse.data->thirstReduce);
				myOwner->GetNeeds()->GetNeedByType(NeedType::Energy)->ChangeByAmount(itemToUse.data->energyBoost);
				myOwner->GetNeeds()->GetNeedByType(NeedType::Happyness)->ChangeByAmount(itemToUse.data->happynessBoost);
				RemoveItemOfID(itemToUse.data->itemID, 1);
				return true;
			}
			else if (itemToUse.data->isEquippable)
			{
				if (!equipment.Find(itemToUse.data->equipType))
				{
					UE_LOG(LogTemp, Error, TEXT("Can't equip - Can't find given equipType!"))
					return false;
				}

				UItemDataAsset*& targetEquipSlot = equipment[itemToUse.data->equipType];
				//If target slot is currently equiped - unequip it
				if (targetEquipSlot && targetEquipSlot->equipType == itemToUse.data->equipType)
				{
					UnequipItem(targetEquipSlot->equipType);
				}
				//Equip item
				targetEquipSlot = itemToUse.data;
				myOwner->EquipVisuals(itemToUse.data->prefab.GetDefaultObject()->GetMesh(), itemToUse.data->equipType);
				RemoveItemOfID(itemToUse.data->itemID, 1);
				UE_LOG(LogTemp, Warning, TEXT("Successfully equiped!"))
				CalculateWeightAndSpace();
				return true;
			}
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("Can't use item - invalid index! Trying to get %i from array of size %i"), index, items.Num())
	return false;
}

bool UInventoryComponent::DropItemOfIndex(const int& index)
{
	if (items.IsValidIndex(index))
	{
		FItemInstance& itemToDrop = items[index];
		TSubclassOf<AItemActor> itemToSpawn = itemToDrop.data->prefab;
		GetWorld()->SpawnActor<AItemActor>(itemToSpawn, GetOwner()->GetActorLocation(), FRotator(0, UKismetMathLibrary::RandomFloatInRange(0, 360), 0));
		RemoveItemOfID(itemToDrop.data->itemID, 1);
		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("Can't drop item - invalid index! Trying to get %i from array of size %i"), index, items.Num())
	return false;
}

bool UInventoryComponent::UnequipItem(const EquipType& equipType)
{
	AAICharacter* myOwner = Cast<AAICharacter>(GetOwner());
	if (!equipment.Find(equipType))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't unequip - Given equipType is null!"))
		return false;
	}

	UItemDataAsset* targetEquipSlot = equipment[equipType];
	if (targetEquipSlot)
	{
		//Remove item from equiped items, refresh space and weight
		myOwner->UnequipVisuals(equipType);
		equipment[equipType] = nullptr;
		CalculateWeightAndSpace();

		//Add unequiped item to inventory
		AddItem(FItemInstance{ targetEquipSlot, 1 });
		
		UE_LOG(LogTemp, Warning, TEXT("Successfully unequiped!"))
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't equip - Given equipType slot is null!"))
	}

	return false;
}

UItemDataAsset* UInventoryComponent::GetEquipedItem(const EquipType& equipType) const
{
	return *equipment.Find(equipType);
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

float UInventoryComponent::CalculateItemsCost() const
{
	float result = 0.0f;
	for (const FItemInstance& currItem : items)
	{
		result += currItem.data->cost * currItem.amount;
	}
	return result;
}

void UInventoryComponent::CalculateWeightAndSpace()
{
	currentWeight = 0;
	currentSpace = 0;
	//Inventory
	for (const FItemInstance& currItem : items)
	{
		currentWeight += currItem.data->weight * currItem.amount;
		currentSpace += currItem.data->space * currItem.amount;
	}
	//Equipment
	for (const TPair<EquipType, UItemDataAsset*>& currItem : equipment)
	{
		if (IsValid(currItem.Value))
		{
			currentWeight += currItem.Value->weight;
			currentSpace += currItem.Value->space;
		}
	}
}

float UInventoryComponent::GetCurrentWeight() const
{
	return currentWeight;
}

float UInventoryComponent::GetMaxWeight() const
{
	return maxWeight;
}

float UInventoryComponent::GetCurrentSpace() const
{
	return currentSpace;
}

float UInventoryComponent::GetMaxSpace() const
{
	return maxSpace;
}

void UInventoryComponent::RefreshUI()
{
	APlayerGameMode* gameMode = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode)
	{
		gameMode->GetUIManager()->RefreshOpenedInventoryPanels();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't refresh inventory UI - GameMode is null!"))
	}
}
