// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableBase.h"

// Sets default values
ABuildableBase::ABuildableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABuildableBase::GetWorkAmountToBuild() const
{
	return workAmountToBuild;
}

const TArray<FItemAssetAmountData>& ABuildableBase::GetBuildRequirements() const
{
	return buildRequirements;
}

bool ABuildableBase::CanBePlaced()
{
	return !isOverlapping;
}

