// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildablePrototype.h"
#include "../PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

ABuildablePrototype::ABuildablePrototype()
{
	PrimaryActorTick.bCanEverTick = true;
	destroyOnSuccessfulInteraction = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	myWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	myWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	box->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	box->SetGenerateOverlapEvents(true);
	box->OnComponentBeginOverlap.AddDynamic(this, &ABuildablePrototype::OnOverlapBegin);
	box->OnComponentEndOverlap.AddDynamic(this, &ABuildablePrototype::OnOverlapEnd);

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

void ABuildablePrototype::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerGameMode* gameMode = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ABuildingManager* buildingManager = gameMode->GetBuildingManager();
	meshComp->SetMaterial(0, buildingManager->GetBadMaterial());

	isOverlapping = true;
}

void ABuildablePrototype::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerGameMode* gameMode = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ABuildingManager* buildingManager = gameMode->GetBuildingManager();
	meshComp->SetMaterial(0, buildingManager->GetGoodMaterial());

	isOverlapping = false;
}

bool ABuildablePrototype::CanBePlaced() const
{
	return !isOverlapping;
}
