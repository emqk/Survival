// Fill out your copyright notice in the Description page of Project Settings.


#include "Conversation.h"
#include "DrawDebugHelpers.h"

void UConversation::Init(const FVector& _location, AAICharacter* starting, AAICharacter* target)
{
	location = _location;
	AddCharacter(starting);
	AddCharacter(target);
}

void UConversation::Cleanup()
{
	UE_LOG(LogTemp, Warning, TEXT("Conversation cleaned up(and now is waiting for GC)!"))
	for (int i = characters.Num() - 1; i >= 0; i--)
	{
		RemoveCharacter(characters[i]);
	}
}

bool UConversation::TickConversation(const float& deltaTime)
{
	DrawDebug();

	for (int i = characters.Num()-1; i >= 0; i--)
	{
		UStatistic* characterSocialNeed = characters[i]->GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Social);
		if (characterSocialNeed->GetAmount() >= endConversationThreshold)
		{
			RemoveCharacter(characters[i]);
		}
		else
		{
			characterSocialNeed->ChangeByAmount(socialNeedPerSec * deltaTime);
		}
	}

	return characters.Num() >= 2;
}

void UConversation::AddCharacter(AAICharacter* character)
{
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

FVector UConversation::GetLocation() const
{
	return location;
}

void UConversation::DrawDebug() const
{
	DrawDebugSphere(GetWorld(), location, 15, 10, FColor(200, 200, 200), false, 0.1f, 0, 1); //Visualize center
	DrawDebugSphere(GetWorld(), location, radius, 10, FColor(160, 160, 160), false, 0.1f, 0, 1); //Visualize radius
}