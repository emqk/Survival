// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildablePrototype.h"

ABuildablePrototype::ABuildablePrototype()
{
	PrimaryActorTick.bCanEverTick = true;
	destroyOnSuccessfulInteraction = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	myWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	myWidget->AttachToComponent(meshComp, FAttachmentTransformRules::KeepRelativeTransform);

	inventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Collected"));
	AddOwnedComponent(inventoryComp);
}

void ABuildablePrototype::SetupVisuals(TSubclassOf<ABuildableBase> toBuildClass)
{
	toBuild = toBuildClass;
	workAmountToBuild = toBuild.GetDefaultObject()->GetWorkAmountToBuild();
	buildRequirements = toBuild.GetDefaultObject()->GetBuildRequirements();
}

void ABuildablePrototype::GiveNeededItems(UInventoryComponent* inventory)
{
	for (const FItemInstance& item : buildRequirements)
	{
		int currAmount = 0;
		int itemIndex = inventoryComp->GetItemIndex(item.data->itemID);
		if (itemIndex >= 0)
			currAmount = inventoryComp->GetItems()[itemIndex].amount;
		int needAmount = FMath::Max(item.amount - currAmount, 0);

		inventory->MoveItem(item.data->itemID, needAmount, inventoryComp);
	}

	RefreshText();
}