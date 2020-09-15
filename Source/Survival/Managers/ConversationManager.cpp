// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationManager.h"

// Sets default values
AConversationManager::AConversationManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConversationManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AConversationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickConversations(DeltaTime);
}

void AConversationManager::StartConversation(AAICharacter* starting, AAICharacter* target)
{
	if (starting->GetIsTalking())
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting is currently talking [RETURN]"))
		return;
	}
	if (target->GetIsTalking())
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is currently talking (Can't start conversation!)"))
		return;
	}
	if (!starting->IsEnabled() || !target->IsEnabled())
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't start conversation - starting or target has ActorTick disabled!"))
		return;
	}

	UConversation* newConversation = NewObject<UConversation>(this);
	FVector conversationLocation = (starting->GetActorLocation() + target->GetActorLocation()) / 2.0f;
	newConversation->Init(conversationLocation, starting, target);
	conversations.Add(newConversation);
}

UConversation* AConversationManager::FindExistingConversationForLocation(const FVector& location) const
{
	for (UConversation* conv : conversations)
	{
		if (conv->IsInRange(location))
		{
			return conv;
		}
	}

	return nullptr;
}

UConversation* AConversationManager::GetConversation(const AAICharacter* character) const
{
	for (UConversation* conv : conversations)
	{
		if (conv->Contains(character))
		{
			return conv;
		}
	}

	return nullptr;
}

void AConversationManager::TickConversations(const float& deltaTime)
{
	for (int i = conversations.Num()-1; i >= 0; i--)
	{
		if (!conversations[i]->TickConversation(deltaTime))
		{
			conversations[i]->Cleanup();
			conversations.RemoveAt(i);
		}
	}
}