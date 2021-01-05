// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCPersonality.h"

FPrimaryAssetId UNPCPersonality::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("Personalities"), GetFName());
}

EPersonalityCategory UNPCPersonality::GetCategory() const
{
	return category;
}

float UNPCPersonality::GetSocialMultiplier() const
{
	return socialMultiplier;
}

float UNPCPersonality::GetHappynessMultiplier() const
{
	return happynessMultiplier;
}

FText UNPCPersonality::GetPersonalityDisplayText() const
{
	return personalityDisplayText;
}
