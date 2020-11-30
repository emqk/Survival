// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengeGroup.h"

FScavengeGroup::FScavengeGroup()
	: scavengeType(ScavengeType::None), group(TArray<AAICharacter*>()), scavagePoint(nullptr)
{
	}

FScavengeGroup::FScavengeGroup(const ScavengeType& _scavengeType, AScavengePoint* _scavengePoint, const TArray<AAICharacter*>& _group)
	: scavengeType(_scavengeType), scavagePoint(_scavengePoint), group(_group)
{
}
