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
		float distToCharacterSq = (location - characters[i]->GetActorLocation()).SizeSquared();
		UStatistic* characterSocialNeed = characters[i]->GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Social);
		if (characterSocialNeed->GetAmount() >= endConversationThreshold || distToCharacterSq > radiusSq)
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

bool UConversation::Contains(const AAICharacter* character)
{
	return characters.Contains(character);
}

FVector UConversation::GetLocation() const
{
	return location;
}

void UConversation::DrawDebug() const
{
	DrawDebugSphere(GetWorld(), location, 15, 10, FColor(200, 200, 200), false, 0.1f, 0, 1); //Visualize center
	DrawDebugSphere(GetWorld(), location, radius, 10, FColor(160, 160, 160), false, 0.1f, 0, 1); //Visualize radius

	for (const AAICharacter* character : characters)
	{
		FVector characterLocation = character->GetActorLocation() + FVector(0, 0, 110);
		DrawDebugSphere(GetWorld(), characterLocation, 15, 3, FColor(0, 255, 0), false);
		DrawDebugLine(GetWorld(), location, characterLocation, FColor(0, 255, 0), false, -1.0f, 0, 2);
	}
}