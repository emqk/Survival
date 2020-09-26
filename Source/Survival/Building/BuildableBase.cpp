// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildableBase.h"

// Sets default values
ABuildableBase::ABuildableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	box->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	box->SetCollisionProfileName("BlockAll");

	destructibleComp = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleComponent"));
	AddOwnedComponent(destructibleComp);
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