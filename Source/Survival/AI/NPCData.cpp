// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCData.h"

UNPCData::UNPCData()
{
	health = NewObject<UStatistic>();
	myNeeds = NewObject<UNPCNeeds>();
	myRelations = NewObject<UNPCRelations>();
}

UNPCData::~UNPCData()
{
}

UNPCNeeds* UNPCData::GetNeeds() const
{
	return myNeeds;
}

UNPCRelations* UNPCData::GetRelations() const
{
	return myRelations;
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