// Fill out your copyright notice in the Description page of Project Settings.


#include "Conversation.h"

void UConversation::Init(const FVector& _location, AAICharacter* starting, AAICharacter* target)
{
	location = _location;
	AddCharacter(starting);
	AddCharacter(target);
}

void UConversation::AddCharacter(AAICharacter* character)
{
	characters.Add(character);
}

void UConversation::RemoveCharacter(AAICharacter* character)
{
	characters.Remove(character);
}

FVector UConversation::GetLocation() const
{
	return location;
}