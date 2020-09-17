// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengeTrip.h"

FScavengeTrip::FScavengeTrip()
	: group(TArray<AAICharacter*>()), scavengePoint(nullptr), timeToGoBackLeft(0), timeToGoBackStart(0)
{
}

FScavengeTrip::FScavengeTrip(const TArray<AAICharacter*>& _group, AScavengePoint* _scavengePoint, const float& _timeToGoBack, const ScavengeType& _scavengeType)
	: group(_group), scavengePoint(_scavengePoint), timeToGoBackStart(_timeToGoBack), timeToGoBackLeft(_timeToGoBack), scavengeType(_scavengeType)
{
}

float FScavengeTrip::GetTimeToGoBackStart() const
{
	return timeToGoBackStart;
}
