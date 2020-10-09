// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCStatus.h"

FPrimaryAssetId UNPCStatus::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("Statuses"), GetFName());
}

void UNPCStatus::TickMe(UNPCNeeds* ownerNeeds, const float& deltaTime)
{
	UE_LOG(LogTemp, Error, TEXT("Default status tick!"))
}
