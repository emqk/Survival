// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCNeeds.h"

const float UNPCNeeds::socialNeedThresholdToAutoJoin = 10.0f;
const float UNPCNeeds::socialNeedThresholdToAutoStart = 1.0f;


UNPCNeeds::UNPCNeeds()
{
	needs.Add(NeedType::Hunger, NewObject<UStatistic>());
	needs.Add(NeedType::Thirst, NewObject<UStatistic>());
	needs.Add(NeedType::Energy, NewObject<UStatistic>());
	needs.Add(NeedType::Happyness, NewObject<UStatistic>());
	needs.Add(NeedType::Social, NewObject<UStatistic>());
}

UNPCNeeds::~UNPCNeeds()
{
}

UStatistic* UNPCNeeds::GetNeedByType(NeedType type) const
{
	return needs[type];
}