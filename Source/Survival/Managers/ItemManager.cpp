// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "Engine/AssetManager.h"

// Sets default values
UItemManager::UItemManager()
{
}

UItemDataAsset* UItemManager::GetItemData(const FName& id) const
{
	FPrimaryAssetType assetType = FPrimaryAssetType("Items");

	TArray<FAssetData> assetDataList;
	UAssetManager& assetMan = UAssetManager::Get();
	bool b = assetMan.GetPrimaryAssetDataList(assetType, assetDataList);
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
