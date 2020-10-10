// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCStatuses.h"

void UNPCStatuses::TickStatuses(UNPCNeeds* ownerNeeds, const float& deltaTime)
{
	for (UNPCStatus* status : statuses)
	{
		status->TickMe(ownerNeeds, deltaTime);
	}
}

void UNPCStatuses::AddStatus(UNPCStatus* status)
{
	if (status)
	{
		statuses.Add(status);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't add status - argument is null!"));
	}
}

void UNPCStatuses::RemoveStatus(UNPCStatus* status)
{
	statuses.Remove(status);
}
