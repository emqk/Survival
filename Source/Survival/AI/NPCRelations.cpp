// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCRelations.h"

UNPCRelations::UNPCRelations()
{

}

TMap<int, UStatistic*> UNPCRelations::GetRelations() const
{
	return relations;
}

void UNPCRelations::ChangeRelationsWith(const int& characterID)
{
	relations.Add(characterID, NewObject<UStatistic>());
}