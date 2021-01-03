// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCNeeds.h"

const float UNPCNeeds::socialNeedThresholdToAutoJoin = 10.0f;
const float UNPCNeeds::socialNeedThresholdToAutoStart = 1.0f;


UNPCNeeds::UNPCNeeds()
{
	needs.Add(NeedType::Hunger, NewObject<UStatistic>());
	needs.Add(NeedType::Hydration, NewObject<UStatistic>());
	needs.Add(NeedType::Energy, NewObject<UStatistic>());
	UStatistic* happynessStat = needs.Add(NeedType::Happyness, NewObject<UStatistic>());
	UStatistic* socialStat = needs.Add(NeedType::Social, NewObject<UStatistic>());
	UStatistic* healthStat = needs.Add(NeedType::Health, NewObject<UStatistic>());

	//Set all values to max
	for (TPair<NeedType, UStatistic*>& need : needs)
	{
		need.Value->ChangeByAmount(999);
	}
}

UNPCNeeds::~UNPCNeeds()
{
}

UStatistic* UNPCNeeds::GetNeedByType(NeedType type) const
{
	return needs[type];
}