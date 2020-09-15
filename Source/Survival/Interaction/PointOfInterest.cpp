// Fill out your copyright notice in the Description page of Project Settings.


#include "PointOfInterest.h"
#include "DrawDebugHelpers.h"

// Sets default values
APointOfInterest::APointOfInterest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
}

// Called when the game starts or when spawned
void APointOfInterest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APointOfInterest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 10, FColor::Yellow, false, 0, 0, 2); //Visualize radius
}

bool APointOfInterest::ShouldTickIfViewportsOnly() const
{
	return true;
}

