// Fill out your copyright notice in the Description page of Project Settings.
#include "CraftData.h"

FPrimaryAssetId UCraftData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("CraftData"), GetFName());
}

TArray<FItemInstance> UCraftData::GetCraftRequirements() const
{
	return craftRequirements;
}
