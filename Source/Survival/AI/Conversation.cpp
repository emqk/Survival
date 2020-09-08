// Fill out your copyright notice in the Description page of Project Settings.


#include "Conversation.h"

void UConversation::Init(const FVector& _location, AAICharacter* starting, AAICharacter* target)
{
	location = _location;
	AddCharacter(starting);
	AddCharacter(target);
}

void UConversation::TickConversation(const float& deltaTime)
{
	for (AAICharacter* ch : characters)
	{
		ch->GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Social)->ChangeByAmount(socialNeedPerSec * deltaTime);
	}
}

void UConversation::AddCharacter(AAICharacter* character)
{
	characters.Add(character);
	character->SetIsTalking(true);
}

void UConversation::RemoveCharacter(AAICharacter* character)
{
	characters.Remove(character);
	character->SetIsTalking(false);
}

FVector UConversation::GetLocation() const
{
	return location;
}