// Fill out your copyright notice in the Description page of Project Settings.


#include "CrewManager.h"
#include "../AI/Conversation.h"
#include "../PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
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

void ACrewManager::ControlNPCSocialNeeds()
{
	APlayerGameMode* gameMode = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AConversationManager* conversationManager = nullptr;
	if (gameMode)
	{
		conversationManager = gameMode->GetConversationManager();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't get gameMode!"))
		return;
	}
	if (!conversationManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't get Conversation Manager!"))
		return;
	}

	for (AAICharacter* ch : members)
	{
		if (ch->GetIsTalking())
			continue;

		float socialNeedAmount = ch->GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Social)->GetAmount();
		if (socialNeedAmount <= UNPCNeeds::socialNeedThresholdToAutoJoin)
		{
			UConversation* foundConversation = conversationManager->FindExistingConversationForLocation(ch->GetActorLocation());
			if (foundConversation)
			{
				foundConversation->AddCharacter(ch);
				continue;
			}
		}
		if (socialNeedAmount <= UNPCNeeds::socialNeedThresholdToAutoStart)
		{
			AAICharacter* lowSocialNPC = GetFirstNPCOtherThanWithLowSocialInRadius(ch, UConversation::radiusSq);
			if (lowSocialNPC)
			{
				conversationManager->StartConversation(ch, lowSocialNPC);
				continue;
			}
		}
	}
}

AAICharacter* ACrewManager::GetFirstNPCOtherThanWithLowSocialInRadius(const AAICharacter* otherThan, const float& radiusSq) const
{
	for (AAICharacter* ch : members)
	{
		if (ch != otherThan)
		{
			float distSq = (ch->GetActorLocation() - otherThan->GetActorLocation()).SizeSquared();
			if (distSq <= radiusSq)
			{
				return ch;
			}
		}
	}

	return nullptr;
}

AAICharacter* ACrewManager::GetMemeber(const int& uniqueID) const
{
	for (AAICharacter* character : members)
	{
		uint32 currCharID = character->GetUniqueID();
		if (currCharID == uniqueID)
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
	ControlNPCSocialNeeds();
}

