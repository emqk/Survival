// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Inventory/ItemDataAsset.h"
#include "AssetData.h"
#include "Engine/AssetManager.h"
#include "ItemManager.generated.h"

UCLASS(Blueprintable)
class SURVIVAL_API UItemManager : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UItemManager();

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	UItemDataAsset* GetItemData(const FName& id) const;

private:

	UFUNCTION()
	bool CheckItemDuplicates();

	UPROPERTY()
	FName itemsAssetName = "Items";

	TArray<UItemDataAsset*> items;
	TArray<FPrimaryAssetId> itemsAssets;

	UAssetManager* assetManager = nullptr;
};