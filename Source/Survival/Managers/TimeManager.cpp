// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

// Sets default values
ATimeManager::ATimeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickTime(DeltaTime);

	if (!isDay && hours >= dayStartHour && hours < dayEndHour)
	{
		OnDayStart.Broadcast();
		isDay = true;
	}
	else if (isDay && hours >= dayEndHour)
	{
		OnDayEnd.Broadcast();
		isDay = false;
	}
}

FRotator ATimeManager::GetRotationFromTime() const
{
	return FRotator(-FMath::Abs(elapsedTime) + 90, 25, 0);
}

FString ATimeManager::GetFormattedTime() const
{
	FString result;
	result.AppendInt(hours);
	result.Append(":");
	result.AppendInt(minutes);

	return MoveTemp(result);
}

void ATimeManager::TickTime(const float& deltaTime)
{
	elapsedTime += worldTimeSpeed * deltaTime;
	if (elapsedTime > 360.0f)
	{
		elapsedTime -= 360.0f;
	}
	//Refresh hours and minutes
	int tempElapsedTime = elapsedTime * 4;
	hours = ((int)tempElapsedTime / 60) % 24;
	minutes = (int)tempElapsedTime % 60;
}
