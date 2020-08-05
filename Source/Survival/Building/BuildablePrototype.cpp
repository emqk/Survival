// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildablePrototype.h"

ABuildablePrototype::ABuildablePrototype()
{
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(meshComp);

	myWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	myWidget->AttachToComponent(meshComp, FAttachmentTransformRules::KeepRelativeTransform);

	inventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Collected"));
}

void ABuildablePrototype::SetupVisuals(UStaticMesh* staticMesh, UMaterialInterface* material, TSubclassOf<ABuildableBase> toBuildClass)
{
	meshComp->SetStaticMesh(staticMesh);
	meshComp->SetMaterial(0, material);
	toBuild = toBuildClass;
	workAmountToBuild = toBuild.GetDefaultObject()->GetWorkAmountToBuild();
	buildRequirements = toBuild.GetDefaultObject()->GetBuildRequirements();
}

void ABuildablePrototype::GiveNeededItems(UInventoryComponent* inventory)
{
	size_t count = inventory->GetItems().Num();
	for (int i = count - 1; i >= 0; --i)
	{
		FName id = inventory->GetItems()[i].data->itemID;
		inventory->MoveItem(id, inventoryComp);
	}
}