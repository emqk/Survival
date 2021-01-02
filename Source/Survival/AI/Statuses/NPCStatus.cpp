// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCStatus.h"

FPrimaryAssetId UNPCStatus::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("Statuses"), GetFName());
}

void UNPCStatus::TickMe(UNPCNeeds* ownerNeeds, const float& deltaTime)
{
	ownerNeeds->GetNeedByType(NeedType::Hunger)->ChangeByAmount(food * deltaTime);
	ownerNeeds->GetNeedByType(NeedType::Hydration)->ChangeByAmount(hydration * deltaTime);
	ownerNeeds->GetNeedByType(NeedType::Energy)->ChangeByAmount(energy * deltaTime);
	ownerNeeds->GetNeedByType(NeedType::Happyness)->ChangeByAmount(happyness * deltaTime);
	ownerNeeds->GetNeedByType(NeedType::Social)->ChangeByAmount(social * deltaTime);
	ownerNeeds->GetNeedByType(NeedType::Health)->ChangeByAmount(health * deltaTime);
}

FText UNPCStatus::GetStatusDisplayText() const
{
	return statusDisplayText;
}
