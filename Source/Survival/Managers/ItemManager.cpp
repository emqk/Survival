// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

// Sets default values
UItemManager::UItemManager()
{
	assetDataList.Empty();
	assetManager = UAssetManager::GetIfValid();

	if (assetManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManger is nullptr!"))
		return;
	}

	FPrimaryAssetType assetType = FPrimaryAssetType(itemsAssetName);
	bool assetsLoaded = assetManager->GetPrimaryAssetDataList(assetType, assetDataList);
	if (!assetsLoaded)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't load assets data of name: %s"), *itemsAssetName.ToString())
		return;
	}
}

UItemDataAsset* UItemManager::GetItemData(const FName& id) const
{
	for (FAssetData asset : assetDataList)
	{
		UItemDataAsset* castedAsset = Cast<UItemDataAsset>(asset.GetAsset());
		if (castedAsset)
		{
			if (castedAsset->itemID == id)
			{
				return castedAsset;
			}
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find item asset of ID: %s"), *id.ToString())
	return nullptr;
}
