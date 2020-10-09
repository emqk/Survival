// Fill out your copyright notice in the Description page of Project Settings.


#include "Conversation.h"
#include "DrawDebugHelpers.h"

const float UConversation::radius = 300;
const float UConversation::radiusSq = radius * radius;


void UConversation::Init(const FVector& _location, AAICharacter* starting, AAICharacter* target)
{
	location = _location;
	AddCharacter(starting);
	AddCharacter(target);
}

void UConversation::Cleanup()
{
	for (int i = characters.Num() - 1; i >= 0; i--)
	{
		RemoveCharacter(characters[i]);
	}

	UE_LOG(LogTemp, Warning, TEXT("Conversation cleaned up(and now is waiting for GC)!"))
}

bool UConversation::TickConversation(const float& deltaTime)
{
	DrawDebug();

	for (int i = characters.Num()-1; i >= 0; i--)
	{
		UStatistic* characterSocialNeed = characters[i]->GetNeeds()->GetNeedByType(NeedType::Social);
		if (characterSocialNeed->GetAmount() >= endConversationThreshold || !IsInRange(characters[i]->GetActorLocation()) || !characters[i]->IsEnabled())
		{
			RemoveCharacter(characters[i]);
		}
		else
		{
			characterSocialNeed->ChangeByAmount(socialNeedPerSec * deltaTime);
			//Change relations with other NPC in this conversation
			for (int j = characters.Num() - 1; j >= 0; j--)
			{
				if (i != j)
				{
					characters[i]->GetRelations()->ChangeRelationWith(characters[j]->GetUniqueID(), changeRelationPerSec * deltaTime);
				}
			}
		}
	}

	return characters.Num() >= 2;
}

void UConversation::AddCharacter(AAICharacter* character)
{
	if (!character->IsEnabled())
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't add %s to conversation - Actor ticking is disabled!"), *character->GetNPCData()->GetFullName().ToString())
		return;
	}

	characters.Add(character);
	character->SetIsTalking(true);
	UE_LOG(LogTemp, Warning, TEXT("Added to conversation: %s"), *character->GetNPCData()->GetFullName().ToString())
}

void UConversation::RemoveCharacter(AAICharacter* character)
{
	characters.Remove(character);
	character->SetIsTalking(false);
	UE_LOG(LogTemp, Warning, TEXT("Removed from conversation: %s"), *character->GetNPCData()->GetFullName().ToString())
}

bool UConversation::Contains(const AAICharacter* character)
{
	return characters.Contains(character);
}

bool UConversation::IsInRange(const FVector& otherLocation)
{
	return (location - otherLocation).SizeSquared() <= radiusSq;
}

FVector UConversation::GetLocation() const
{
	return location;
}

void UConversation::DrawDebug() const
{
	DrawDebugSphere(GetWorld(), location, 15, 10, FColor(200, 200, 200), false, -1.0f, 0, 1); //Visualize center
	DrawDebugSphere(GetWorld(), location, radius, 20, FColor(160, 160, 160), false, -1.0f, 0, 1); //Visualize radius

	//Visualize NPCs connection to Conversation
	for (const AAICharacter* character : characters)
	{
		FVector characterLocation = character->GetActorLocation() + FVector(0, 0, 110);
		DrawDebugSphere(GetWorld(), characterLocation, 15, 3, FColor(0, 255, 0), false);
		DrawDebugLine(GetWorld(), location, characterLocation, FColor(0, 255, 0), false, -1.0f, 0, 2);
	}
}