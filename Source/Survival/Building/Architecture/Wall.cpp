// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "../../PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
	//Send data about this floor to building manager's array data
	APlayerGameMode* gameMode = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ABuildingManager* buildingManager = gameMode->GetBuildingManager();
	FIntVector vectorIndex = buildingManager->TransformLocationToVectorIndex(GetActorLocation());
	buildingManager->SetWallAt(this, vectorIndex);
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

