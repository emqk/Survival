// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "../Inventory/InventoryComponent.h"

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

bool AItemActor::InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character)
{
	UInventoryComponent* inventory = Cast<UInventoryComponent>(character->GetComponentByClass(UInventoryComponent::StaticClass()));
	inventory->AddItemsFromAsset(afterDestroyItems);

	Destroy();
	return true;
}