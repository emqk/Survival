// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengeManager.h"

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

void AScavengeManager::TickScavengeTrips(const float& deltaTime)
{
	for (int i = scavengeTrips.Num()-1; i >= 0; i--)
	{
		scavengeTrips[i].timeToGoBackLeft -= deltaTime;
		if (scavengeTrips[i].timeToGoBackLeft <= 0)
		{
			EndScavengeTrip(scavengeTrips[i], i);
		}
	}
}

void AScavengeManager::EndScavengeTrip(FScavengeTrip& scavengeTrip, const int& index)
{
	if (scavengeTrips.Contains(scavengeTrip))
	{
		for (AAICharacter* ch : scavengeTrip.group)
		{
			ch->SetMeActive(true);
			ch->inventoryComp->AddItem(scavengeTrip.scavengePoint->GetItemInstance());
			ch->SimulateNeedsOverTime(scavengeTrip.GetTimeToGoBackStart());
		}
		scavengeTrips.RemoveAt(index);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't end trip - given trip doesn't exist!"))
	}
}

// Called every frame
void AScavengeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickScavengeTrips(DeltaTime);
}

void AScavengeManager::SetScavengePoints(AScavengePoint* wood)
{
	woodsInteractionPoint = wood;
}

bool AScavengeManager::CreateScavengeGroup(const TArray<AAICharacter*>& characters, AScavengePoint* targetScavengePoint)
{
	for (const AAICharacter* ch : characters)
	{
		if (IsNPCInAnyScavengeGroup(ch))
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't create a ScavengeGroup - One of the NPCs are in other NPC group!"))
			return false;
		}
	}

	scavengeGroups.Add(FScavengeGroup{characters, targetScavengePoint});
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

bool AScavengeManager::CheckScavengePoint(AScavengePoint* scavengePoint)
{
	for (int i = scavengeGroups.Num() - 1; i >= 0; i--)
	{
		const FScavengeGroup& sg = scavengeGroups[i];
		if (sg.scavagePoint == scavengePoint)
		{
			if (sg.scavagePoint)
			{
				if (scavengePoint->ContainsScavengeGroup(sg))
				{
					scavengePoint->RemoveAndDisableGroup(sg);
					scavengeTrips.Add(FScavengeTrip( sg.group, sg.scavagePoint, 10 ));
					scavengeGroups.RemoveAt(i);
				}
			}
		}
	}

	return false;
}

void AScavengeManager::SetWoodsInteractionPoint(AScavengePoint* point)
{
	woodsInteractionPoint = point;
}

AScavengePoint* AScavengeManager::GetWoodsInteractionPoint() const
{
	return woodsInteractionPoint;
}

