// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengeManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AScavengeManager::AScavengeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScavengeManager::BeginPlay()
{
	Super::BeginPlay();
}

void AScavengeManager::TickScavengeGroups(const float& deltaTime)
{
	for (int i = scavengeGroups.Num()-1; i >= 0; i--)
	{
		if (!scavengeGroups[i].IsOnTrip())
			continue;

		scavengeGroups[i].TickMe(deltaTime);
		if (scavengeGroups[i].IsTripFinished())
		{
			EndScavengeGroup(scavengeGroups[i], i);
		}
	}

	//Refresh UI
	if (scavengePoints.Num() > 0)
	{
		scavengePoints[0]->RefreshMyWidget(scavengeGroups);
	}
}

void AScavengeManager::EndScavengeGroup(FScavengeGroup& scavengeGroup, const int& index)
{
	if (scavengeGroups.Contains(scavengeGroup))
	{
		for (AAICharacter* ch : scavengeGroup.group)
		{
			ch->SetMeActive(true);
			//Add items from scavenge
			ch->inventoryComp->AddItemsFromAsset(GenerateItemsFromScavenge(scavengeGroup.scavengeType));
			ch->SimulateNeedsOverTime(scavengeGroup.GetTimeToGoBackStart());
		}
		scavengeGroups.RemoveAt(index);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't end trip - given trip doesn't exist!"))
	}
}

TArray<FItemInstance> AScavengeManager::GenerateItemsFromScavenge(const ScavengeType& scavengeType) const
{
	TArray<FItemInstance> result;
	const FScavengeItems items = itemsFromScavenge[scavengeType];
	result.Reserve(items.items.Num());
	for (const FItemsRandomizeData& i : items.items)
	{
		result.Add(FItemInstance{ i.itemToGet, UKismetMathLibrary::RandomIntegerInRange(i.itemAmountMin, i.itemAmountMax) } );
	}

	return result;
}

// Called every frame
void AScavengeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickScavengeGroups(DeltaTime);
}

void AScavengeManager::SetScavengePoints()
{
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScavengePoint::StaticClass(), foundActors);
	
	scavengePoints.Empty();
	scavengePoints.Reserve(foundActors.Num());
	for (AActor* a : foundActors)
	{
		AScavengePoint* castedActor = Cast<AScavengePoint>(a);
		if (a)
		{
			scavengePoints.Add(castedActor);
		}
	}
}

bool AScavengeManager::CreateScavengeGroup(const TArray<AAICharacter*>& characters, AScavengePoint* targetScavengePoint, const ScavengeType& scavengeType)
{
	for (const AAICharacter* ch : characters)
	{
		if (IsNPCInAnyScavengeGroup(ch))
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't create a ScavengeGroup - One of the NPCs are in other NPC group!"))
			return false;
		}
	}

	scavengeGroups.Add(FScavengeGroup(scavengeType, targetScavengePoint, characters, 5));
	CheckAllScavengePoints();
	return true;
}

bool AScavengeManager::IsNPCInAnyScavengeGroup(const AAICharacter* character) const
{
	for (const FScavengeGroup& sg : scavengeGroups)
	{
		if (sg.group.Contains(character))
			return true;
	}

	return false;
}

void AScavengeManager::CheckAllScavengePoints()
{
	for (AScavengePoint* sp : scavengePoints)
	{
		CheckScavengePoint(sp);
	}
}

bool AScavengeManager::CheckScavengePoint(AScavengePoint* scavengePoint)
{
	for (int i = scavengeGroups.Num() - 1; i >= 0; i--)
	{
		FScavengeGroup& sg = scavengeGroups[i];
		if (sg.scavagePoint == scavengePoint)
		{
			if (sg.scavagePoint && !sg.IsOnTrip())
			{
				if (scavengePoint->ContainsScavengeGroup(sg))
				{
					scavengePoint->DisableGroupCharacters(sg);
					sg.StartTrip();
					return true;
				}
			}
		}
	}

	return false;
}

AScavengePoint* AScavengeManager::GetRandomScavengePoint() const
{
	return GetScavengePoint(UKismetMathLibrary::RandomIntegerInRange(0, scavengePoints.Num()-1));
}

AScavengePoint* AScavengeManager::GetScavengePoint(const int& index) const
{
	if (scavengePoints.IsValidIndex(index))
	{
		return scavengePoints[index];
	}
	return nullptr;
}

bool AScavengeManager::RemoveScavengeGroupAtIndex(const int& index)
{
	if (scavengeGroups.IsValidIndex(index))
	{
		//Stop all AI in given scavenge group from going to target scavenge point
		for (AAICharacter* ai : scavengeGroups[index].group)
		{
			ai->CancelCurrentInteraction();
		}
		scavengeGroups.RemoveAt(index);
		return true;
	}

	return false;
}
