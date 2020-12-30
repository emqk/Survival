// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "../Inventory/InventoryComponent.h"

AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	mesh->SetSimulatePhysics(true);
	SetRootComponent(mesh);
	sceneComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
}

void AItemActor::InitItemsAfterCollect(const FItemInstance& item)
{
	afterCollectItem = item;
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AItemActor::InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character)
{
	//Add item to inventory
	UInventoryComponent* inventory = character->FindComponentByClass<UInventoryComponent>();
	if (!inventory->AddItem(afterCollectItem))
		return true; // If item can't be added - stop interaction and don't collect this item

	Destroy();
	return true;
}

UStaticMesh* AItemActor::GetMesh() const
{
	return mesh->GetStaticMesh();
}