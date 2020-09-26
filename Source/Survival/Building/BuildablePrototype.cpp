// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildablePrototype.h"
#include "../UI/Building/BuildingPrototypeWidget.h"
#include "../PlayerGameMode.h"
#include "../Interaction/ItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABuildablePrototype::ABuildablePrototype()
{
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	meshComp->SetCollisionProfileName("NoCollision");

	myWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	myWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	myWidget->SetCollisionProfileName("NoCollision");

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	box->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	box->SetGenerateOverlapEvents(true);
	box->OnComponentBeginOverlap.AddDynamic(this, &ABuildablePrototype::OnOverlapBegin);
	box->OnComponentEndOverlap.AddDynamic(this, &ABuildablePrototype::OnOverlapEnd);
	
	inventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Collected"));
	AddOwnedComponent(inventoryComp);

	destructibleComp = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleComponent"));
	AddOwnedComponent(destructibleComp);
}

void ABuildablePrototype::Setup(TSubclassOf<ABuildableBase> toBuildClass)
{
	toBuild = toBuildClass;
	RefreshText();
}

void ABuildablePrototype::CancelBuilding()
{
	UWorld* world = GetWorld();
	for (const FItemInstance& item : inventoryComp->GetItems())
	{
		TSubclassOf<AItemActor> actor = item.data->prefab;
		world->SpawnActor<AItemActor>(actor, GetActorLocation(), FRotator(0, UKismetMathLibrary::RandomFloatInRange(0, 360), 0));
	}

	Destroy();
}

void ABuildablePrototype::RefreshText()
{
	UBuildingPrototypeWidget* buildingWidget = Cast<UBuildingPrototypeWidget>(myWidget->GetUserWidgetObject());
	if (buildingWidget)
	{
		buildingWidget->SetupTexts(buildRequirements, inventoryComp);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't cast to UBuildingPrototypeWidget!"))
	}
}

bool ABuildablePrototype::InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character)
{
	if (HaveRequiredItems())
	{
		if (ConstructTick(deltaSeconds, character->GetBuildSpeed(), character->GetDestructionSpeed()))
		{
			Destroy();
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool ABuildablePrototype::ConstructTick(const float& deltaTime, const float& buildSpeed, const float& destructionSpeed)
{
	currentWorkAmount += buildSpeed * deltaTime;
	if (currentWorkAmount >= workAmountToBuild)
	{
		Build();
		return true;
	}

	return false;
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
	OnOverlap();
}

void ABuildablePrototype::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnOverlap();
}

void ABuildablePrototype::OnOverlap()
{
	TSet<AActor*> overlappingActors;
	box->GetOverlappingActors(overlappingActors);
	if (overlappingActors.Num() > 0)
	{
		//Ignore AICharacters
		for (AActor* a : overlappingActors)
		{
			if (!Cast<AAICharacter>(a))
				isOverlapping = true;
		}
	}
	else
		isOverlapping = false;

	APlayerGameMode* gameMode = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ABuildingManager* buildingManager = gameMode->GetBuildingManager();

	if (isOverlapping)
		meshComp->SetMaterial(0, buildingManager->GetBadMaterial());
	else
		meshComp->SetMaterial(0, buildingManager->GetGoodMaterial());
}

void ABuildablePrototype::Build()
{
	GetWorld()->SpawnActor<ABuildableBase>(toBuild, GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), finishBuildSound, GetActorLocation());
}

float ABuildablePrototype::GetWorkAmountToBuild() const
{
	return workAmountToBuild;
}

const TArray<FItemInstance>& ABuildablePrototype::GetBuildRequirements() const
{
	return buildRequirements;
}

bool ABuildablePrototype::HaveRequiredItems() const
{
	return inventoryComp->HaveAmountOfItems(buildRequirements);
}

bool ABuildablePrototype::CanBePlaced() const
{
	return !isOverlapping;
}
