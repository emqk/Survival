// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"

AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}