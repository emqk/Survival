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

void AItemActor::InitItemsAfterDestroy(const TArray<FItemInstance>& items)
{
	afterDestroyItems = items;
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AItemActor::InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character)
{
	//Add item to inventory
	UInventoryComponent* inventory = character->FindComponentByClass<UInventoryComponent>();
	inventory->AddItemsFromAsset(afterDestroyItems);
	Destroy();
	return true;
}

UStaticMesh* AItemActor::GetMesh() const
{
	return mesh->GetStaticMesh();
}