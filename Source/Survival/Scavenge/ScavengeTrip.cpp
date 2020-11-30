// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengeTrip.h"

FScavengeTrip::FScavengeTrip()
	: scavengeGroup(), timeToGoBackLeft(0), timeToGoBackStart(0)
{

}

FScavengeTrip::FScavengeTrip(const ScavengeType& _scavengeType, class AScavengePoint* _scavengePoint, const TArray<AAICharacter*>& _group, const float& _timeToGoBack)
	: scavengeGroup(_scavengeType, _scavengePoint, _group), timeToGoBackStart(_timeToGoBack), timeToGoBackLeft(_timeToGoBack)
{
}

float FScavengeTrip::GetTimeToGoBackStart() const
{
	return timeToGoBackStart;
}
