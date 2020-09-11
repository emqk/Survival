// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingManager.h"

// Sets default values
ABuildingManager::ABuildingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuildingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingManager::BeginBuilding()
{
	if (!currentFloor)
	{
		currentFloor = GetWorld()->SpawnActor<AActor>(floorToBuild, FVector(0, 0, 0), FRotator(0, 0, 0));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't BeginBuilding - currentFloor is not null!"))
	}
}

void ABuildingManager::TickBuilding(const FVector& mouseHit)
{
	if (currentFloor)
	{
		FVector snapLocation = mouseHit / snapSize;
		snapLocation = FVector(FMath::RoundToInt(snapLocation.X), FMath::RoundToInt(snapLocation.Y), 0) * snapSize;
		currentFloor->SetActorLocation(snapLocation);
	}
}

void ABuildingManager::EndBuilding()
{
	if (currentFloor)
	{
		currentFloor = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't EndBuilding - currentFloor is null!"))
	}
}
