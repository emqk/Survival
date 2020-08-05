// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildablePrototype.h"

ABuildablePrototype::ABuildablePrototype()
{
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(meshComp);

	myWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	myWidget->AttachToComponent(meshComp, FAttachmentTransformRules::KeepRelativeTransform);

	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

}

void ABuildablePrototype::SetupCPP(UStaticMesh* staticMesh, UMaterialInterface* material, TSubclassOf<ABuildableBase> toBuildClass)
{
	meshComp->SetStaticMesh(staticMesh);
	meshComp->SetMaterial(0, material);
	toBuild = toBuildClass;
	workAmountToBuild = toBuild.GetDefaultObject()->GetWorkAmountToBuild();
	buildRequirements = toBuild.GetDefaultObject()->GetBuildRequirements();
}