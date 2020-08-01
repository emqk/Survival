// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCNeeds.h"

UNPCNeeds::UNPCNeeds()
{
	needs.Add(std::make_pair(NeedType::Hunger, NewObject<UStatistic>()));
	needs.Add(std::make_pair(NeedType::Thirst, NewObject<UStatistic>()));
	needs.Add(std::make_pair(NeedType::Energy, NewObject<UStatistic>()));
	needs.Add(std::make_pair(NeedType::Happyness, NewObject<UStatistic>()));
}


UNPCNeeds::~UNPCNeeds()
{
}

UStatistic* UNPCNeeds::GetNeedByType(NeedType type) const
{
	return needs[(int)type].second;
}
