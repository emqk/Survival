// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCData.h"

UNPCData::UNPCData()
{
	
}

UNPCData::~UNPCData()
{
}

FPrimaryAssetId UNPCData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("NPCData"), GetFName());
}

FName UNPCData::GetFullName() const
{
	FString str = name.ToString();
	str.Append(" ");
	str.Append(surname.ToString());
	return FName(str);
}

void UNPCData::SetFullName(const FName& newName, const FName& newSurname)
{
	name = newName;
	surname = newSurname;
}