// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCData.h"

UNPCData::UNPCData()
{
	UE_LOG(LogTemp, Warning, TEXT("NPCData ctor"))
	myNeeds = NewObject<UNPCNeeds>();
}

UNPCData::~UNPCData()
{
}

UNPCNeeds* UNPCData::GetNeeds() const
{
	return myNeeds;
}

void UNPCData::SetFullName(const FName& newName, const FName& newSurname)
{
	name = newName;
	surname = newSurname;
}
