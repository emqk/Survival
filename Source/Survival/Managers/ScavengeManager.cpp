// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengeManager.h"

// Sets default values
AScavengeManager::AScavengeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScavengeManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScavengeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScavengeManager::SetScavengePoints(AScavengePoint* wood)
{
	woodsInteractionPoint = wood;
}

void AScavengeManager::SetWoodsInteractionPoint(AScavengePoint* point)
{
	woodsInteractionPoint = point;
}

AScavengePoint* AScavengeManager::GetWoodsInteractionPoint() const
{
	return woodsInteractionPoint;
}

