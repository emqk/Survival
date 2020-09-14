// Fill out your copyright notice in the Description page of Project Settings.


#include "ScavengePoint.h"
#include "DrawDebugHelpers.h"

AScavengePoint::AScavengePoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScavengePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 10, FColor::Yellow, false, 0, 0, 2); //Visualize radius
}

bool AScavengePoint::ShouldTickIfViewportsOnly() const
{
	return true;
}

bool AScavengePoint::InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character)
{
	UE_LOG(LogTemp, Error, TEXT("Hey, you need to implement interaction for me :)"))
	return false;
}
