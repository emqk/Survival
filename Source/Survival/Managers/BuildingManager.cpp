// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

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
	walls.Init(nullptr, (width + 1) * (height + 1));
}

// Called every frame
void ABuildingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Debug draw marked to destroy actors
	for (const AActor* actor : markedToDestroy)
	{
		DrawDebugSphere(GetWorld(), actor->GetActorLocation(), 50, 20, FColor(255, 0, 0), false, -1.0f, 0, 1);
	}
}

void ABuildingManager::BeginBuilding(TSubclassOf<ABuildableBase> buildable, ABuildablePrototype* prototype)
{
	if (currentPrototype)
	{
		currentPrototype->Destroy();
	}

	if (buildable->IsChildOf(AFloor::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("It's floor!"))
		currentFloor = buildable;
		currentWall = nullptr;
		currentBuildable = nullptr;
	}
	else if(buildable->IsChildOf(AWall::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("It's wall!"))
		currentFloor = nullptr;
		currentWall = buildable;
		currentBuildable = nullptr;
	}
	else if(buildable->IsChildOf(ABuildableBase::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("It's buildable!"))
		currentFloor = nullptr;
		currentWall = nullptr;
		currentBuildable = buildable;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("It's other!"))
	}

	currentPrototype = prototype;
}

void ABuildingManager::TickBuilding(const FVector& mouseHit)
{
	if (currentPrototype)
	{
		if (currentFloor || currentWall)
		{
			FVector snapLocation = TransformToSnap(mouseHit);
			currentPrototype->SetActorLocation(snapLocation);
			currentPrototype->SetActorRotation(FRotator(0, currentRotationY, 0));
		}
		else
		{
			currentPrototype->SetActorLocation(mouseHit);
			currentPrototype->SetActorRotation(FRotator(0, currentRotationY, 0));
		}
	}
}

void ABuildingManager::EndBuilding()
{
	if (!currentPrototype)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't EndBuilding - currentPrototype is null!"))
		return;
	}
	if (!currentPrototype->CanBePlaced())
	{
		UE_LOG(LogTemp, Error, TEXT("Can't EndBuilding - Can not be placed!"))
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), buildSound, currentPrototype->GetActorLocation());
	UBoxComponent* boxCollider = Cast<UBoxComponent>(currentPrototype->GetComponentByClass(UBoxComponent::StaticClass()));
	boxCollider->SetCollisionProfileName(afterPlacingProtCollisionProfile);
	currentPrototype = nullptr;
}

void ABuildingManager::CancelBuilding()
{
	if (currentPrototype)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), cancelBuildingSound, currentPrototype->GetActorLocation());
		currentPrototype->Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't CancelBuilding - Current Prototype is nullptr!"))
	}
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

bool ABuildingManager::SetWallAt(AWall* wall, const FIntVector& vectorIndex)
{
	int index = vectorIndex.Y + (vectorIndex.X * (width + 1));
	if (walls.IsValidIndex(index) && IsWallVectorIndexValid(vectorIndex))
	{
		walls[index] = wall;
		UE_LOG(LogTemp, Warning, TEXT("Wall set on %ix, %iy, %iz  index: %i"), vectorIndex.X, vectorIndex.Y, vectorIndex.Z, index)
			return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't set wall at %ix, %iy, %iz  index: %i"), vectorIndex.X, vectorIndex.Y, vectorIndex.Z, index)
			return false;
	}
}


FVector ABuildingManager::TransformToSnap(const FVector& mouseHit) const
{
	FIntVector index = TransformLocationToVectorIndex(mouseHit);
	FVector snapLocation = FVector(index.X, index.Y, 0) * snapSize;
	return snapLocation;
}

void ABuildingManager::ChangeRotationY(const float& amount)
{
	currentRotationY += amount;
}

bool ABuildingManager::IsBuilding() const
{
	return IsValid(currentPrototype);
}

FIntVector ABuildingManager::TransformLocationToVectorIndex(const FVector& mouseHit) const
{
	FVector mouseHitReduced = mouseHit / snapSize;
	FIntVector index = FIntVector(FMath::RoundToInt(mouseHitReduced.X), FMath::RoundToInt(mouseHitReduced.Y), FMath::RoundToInt(mouseHitReduced.Z));
	return index;
}

UMaterialInterface* ABuildingManager::GetGoodMaterial() const
{
	return goodMaterial;
}

UMaterialInterface* ABuildingManager::GetBadMaterial() const
{
	return badMaterial;
}

void ABuildingManager::MarkToDestroy(AActor* toDestroy)
{
	markedToDestroy.Add(toDestroy);
	UE_LOG(LogTemp, Warning, TEXT("Marked to destroy!"))
}

bool ABuildingManager::IsVectorIndexValid(const FIntVector& vectorIndex) const
{
	return (vectorIndex.X >= 0 && vectorIndex.X < width), (vectorIndex.Y >= 0 && vectorIndex.Y < height);
}

bool ABuildingManager::IsWallVectorIndexValid(const FIntVector& vectorIndex) const
{
	return (vectorIndex.X >= 0 && vectorIndex.X <= width), (vectorIndex.Y >= 0 && vectorIndex.Y <= height);
}
