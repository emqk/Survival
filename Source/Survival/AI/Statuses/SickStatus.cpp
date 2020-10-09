// Fill out your copyright notice in the Description page of Project Settings.


#include "SickStatus.h"

void USickStatus::TickMe(UNPCNeeds* ownerNeeds, const float& deltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Sick!"));
	ownerNeeds->GetNeedByType(NeedType::Energy)->ChangeByAmount(someValue * deltaTime);
}
