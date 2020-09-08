// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCRelations.h"

UNPCRelations::UNPCRelations()
{

}

TMap<int, UStatistic*> UNPCRelations::GetRelations() const
{
	return relations;
}

void UNPCRelations::ChangeRelationWith(const int& characterID, const float& amount)
{
	if (relations.Contains(characterID))
	{
		relations[characterID]->ChangeByAmount(amount);
	}
	else
	{
		relations.Add(characterID, NewObject<UStatistic>())->ChangeByAmount(amount);
	}
}