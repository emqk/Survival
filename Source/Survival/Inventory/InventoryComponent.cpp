// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../AI/AICharacter.h"
#include "../Interaction/ItemActor.h"
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
	else if(item.amount > 0)
	{
		items.Add(item);
	}

	CalculateWeightAndSpace();
}

bool UInventoryComponent::RemoveItem(const int32& index)
{
	if (items.IsValidIndex(index))
	{
		items.RemoveAt(index);
		CalculateWeightAndSpace();
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
				myOwner->GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Hunger)->ChangeByAmount(-itemToUse.data->foodReduce);
				myOwner->GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Thirst)->ChangeByAmount(-itemToUse.data->thirstReduce);
				myOwner->GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Energy)->ChangeByAmount(itemToUse.data->energyBoost);
				myOwner->GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Happyness)->ChangeByAmount(itemToUse.data->happynessBoost);
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
		AddItem(FItemInstance{targetEquipSlot, 1});
		myOwner->UnequipVisuals(equipType);
		equipment[equipType] = nullptr;
		CalculateWeightAndSpace();
		UE_LOG(LogTemp, Warning, TEXT("Successfully unequiped!"))
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't equip - Given equipType slot is null!"))
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
