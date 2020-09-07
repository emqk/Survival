// Fill out your copyright notice in the Description page of Project Settings.


#include "CrewManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACrewManager::ACrewManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACrewManager::BeginPlay()
{
	Super::BeginPlay();
}

AAICharacter* ACrewManager::GetMemeber(const int& id) const
{
	for (AAICharacter* character : members)
	{
		uint32 currCharID = character->GetUniqueID();
		if (currCharID == id)
		{
			return character;
		}
	}

	return nullptr;
}

FName ACrewManager::GetRandomName(const TArray<FName>& names)
{
	FRandomStream stream(UKismetMathLibrary::RandomInteger(9999999));
	int index = UKismetMathLibrary::RandomIntegerInRangeFromStream(0, names.Num() - 1, stream);
	return names[index];
}

// Called every frame
void ACrewManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

