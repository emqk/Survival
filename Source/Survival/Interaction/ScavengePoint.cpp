// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengePoint.h"
#include "../PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AScavengePoint::AScavengePoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScavengePoint::BeginPlay()
{
	Super::BeginPlay();
}

void AScavengePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AScavengePoint::ContainsScavengeGroup(const FScavengeGroup& scavengeGroup)
{
	for (size_t i = 0; i < scavengeGroup.group.Num(); i++)
	{
		if (!charactersIn.Contains(scavengeGroup.group[i]))
		{
			return false;
		}
	}

	return true;
}

void AScavengePoint::RemoveAndDisableGroup(const FScavengeGroup& scavengeGroup)
{
	for (size_t i = 0; i < scavengeGroup.group.Num(); i++)
	{
		scavengeGroup.group[i]->SetMeActive(false);
		charactersIn.Remove(scavengeGroup.group[i]);
	}
}

FItemInstance AScavengePoint::GetItemInstance() const
{
	return FItemInstance{ itemToGet, UKismetMathLibrary::RandomIntegerInRange(itemAmountMin, itemAmountMax)};
}

void AScavengePoint::OnBeginOverlap()
{
	APlayerGameMode* gameMode = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AScavengeManager* scavengeManager = gameMode->GetScavengeManager();
	scavengeManager->CheckScavengePoint(this);
}
