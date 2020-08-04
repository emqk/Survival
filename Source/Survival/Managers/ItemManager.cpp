// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
UItemManager::UItemManager()
{

}

void UItemManager::Init()
{
	items.Empty();
	itemsAssets.Empty();
	assetManager = UAssetManager::GetIfValid();

	if (assetManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AssetManger is nullptr!"))
		return;
	}
	FPrimaryAssetType assetType = FPrimaryAssetType(itemsAssetName);
	bool assetsLoaded = assetManager->GetPrimaryAssetIdList(assetType, itemsAssets);
	if (assetsLoaded)
	{
		items.Reserve(itemsAssets.Num());
		for (const FPrimaryAssetId& asset : itemsAssets)
		{
			UItemDataAsset* dataA = Cast<UItemDataAsset>(UKismetSystemLibrary::GetObjectFromPrimaryAssetId(asset));
			if (dataA)
			{
				items.Add(dataA);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't load assets data of name: %s"), *itemsAssetName.ToString())
		return;
	}

	if (CheckItemDuplicates())
	{
		UE_LOG(LogTemp, Error, TEXT("----------> Some items are duplicated (Same ID)!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("----------> No item duplicates (That's Good :) )!"))
	}
}

UItemDataAsset* UItemManager::GetItemData(const FName& id) const
{
	for (UItemDataAsset* asset : items)
	{
		if (asset->itemID == id)
		{
			return asset;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find item asset of ID: %s"), *id.ToString())
	return nullptr;
}

bool UItemManager::CheckItemDuplicates()
{
	bool haveDuplicates = false;
	TArray<FName> duplicatesArr;
	duplicatesArr.Reserve(itemsAssets.Num());

	UE_LOG(LogTemp, Warning, TEXT("Available items:"))
	int i = 0;
	for (UItemDataAsset* item : items)
	{
		if (!duplicatesArr.Contains(item->itemID))
		{
			UE_LOG(LogTemp, Warning, TEXT("%i: name: %s, id: %s"), i, *item->name.ToString(), *item->itemID.ToString())
			duplicatesArr.Add(item->itemID);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("%i. NOT UNIQUE ID: %s | Asset name: %s"), i, *item->itemID.ToString(), *itemsAssets[i].PrimaryAssetName.ToString())
			haveDuplicates = true;
		}
		++i;
	}

	return haveDuplicates;
}
