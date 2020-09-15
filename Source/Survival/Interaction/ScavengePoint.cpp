// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengePoint.h"

AScavengePoint::AScavengePoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScavengePoint::BeginPlay()
{
	Super::BeginPlay();
}

void AScavengePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}