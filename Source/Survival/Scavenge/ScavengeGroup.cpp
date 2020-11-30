// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengeGroup.h"

FScavengeGroup::FScavengeGroup()
	: scavengeType(ScavengeType::None), group(TArray<AAICharacter*>()), scavagePoint(nullptr), timeToGoBackLeft(0), timeToGoBackStart(0), isOnTrip(false)
{
	}

FScavengeGroup::FScavengeGroup(const ScavengeType& _scavengeType, AScavengePoint* _scavengePoint, const TArray<AAICharacter*>& _group, const float& _timeToGoBack)
	: scavengeType(_scavengeType), scavagePoint(_scavengePoint), group(_group), timeToGoBackStart(_timeToGoBack), timeToGoBackLeft(_timeToGoBack), isOnTrip(false)
{
}

void FScavengeGroup::TickMe(const float& deltaTime)
{
	timeToGoBackLeft -= deltaTime;
}

float FScavengeGroup::GetTimeToGoBackStart() const
{
	return timeToGoBackStart;
}

bool FScavengeGroup::IsTripFinished() const
{
	return timeToGoBackLeft <= 0;
}

bool FScavengeGroup::IsOnTrip() const
{
	return isOnTrip;
}

void FScavengeGroup::StartTrip()
{
	isOnTrip = true;
}
