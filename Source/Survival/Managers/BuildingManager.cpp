// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingManager.h"
#include "Kismet/GameplayStatics.h"

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
	floors.Init(nullptr, width * height);
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
		currentFloor = GetWorld()->SpawnActor<AFloor>(floorToBuild, FVector(0, 0, 0), FRotator(0, 0, 0));
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
		FIntVector index = TransformLocationToVectorIndex(mouseHit);
		FVector snapLocation = FVector(index.X, index.Y, 0) * snapSize;
		currentFloor->SetActorLocation(snapLocation);
	}
}

void ABuildingManager::EndBuilding(const FVector& mouseHit)
{
	if (currentFloor)
	{
		FIntVector floorIndex = TransformLocationToVectorIndex(mouseHit);
		if (SetFloorAt(currentFloor, floorIndex))
		{
			currentFloor = nullptr;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), buildSound, mouseHit);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't EndBuilding - currentFloor is null!"))
	}
}

FIntVector ABuildingManager::TransformLocationToVectorIndex(const FVector& mouseHit) const
{
	FVector mouseHitReduced = mouseHit / snapSize;
	FIntVector index = FIntVector(FMath::RoundToInt(mouseHitReduced.X), FMath::RoundToInt(mouseHitReduced.Y), FMath::RoundToInt(mouseHitReduced.Z));
	return index;
}

bool ABuildingManager::SetFloorAt(AFloor* floor, const FIntVector& vectorIndex)
{
	int index = vectorIndex.Y + (vectorIndex.X * width);
	if (floors.IsValidIndex(index) && IsVectorIndexValid(vectorIndex))
	{
		floors[index] = floor;
		UE_LOG(LogTemp, Warning, TEXT("Floor set on %ix, %iy, %iz  index: %i"), vectorIndex.X, vectorIndex.Y, vectorIndex.Z, index)
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't set floor at %ix, %iy, %iz  index: %i"), vectorIndex.X, vectorIndex.Y, vectorIndex.Z, index)
		return false;
	}
}

bool ABuildingManager::IsVectorIndexValid(const FIntVector& vectorIndex) const
{
	return (vectorIndex.X >= 0 && vectorIndex.X < width), (vectorIndex.Y >= 0 && vectorIndex.Y < height);
}
