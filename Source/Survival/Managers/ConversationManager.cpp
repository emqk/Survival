// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationManager.h"
#include "DrawDebugHelpers.h"

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
	DebugDraw();
}

void AConversationManager::StartConversation(AAICharacter* starting, AAICharacter* target)
{
	UConversation* newConversation = NewObject<UConversation>();
	FVector conversationLocation = (starting->GetActorLocation() + target->GetActorLocation()) / 2.0f;
	newConversation->Init(conversationLocation, starting, target);
	conversations.Add(newConversation);
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

void AConversationManager::DebugDraw() const
{
	for (const UConversation* currConversation : conversations)
	{
		FVector convLocation = currConversation->GetLocation();
		DrawDebugSphere(GetWorld(), convLocation, 50, 10, FColor(255, 0, 0), false, 0.1f, 0, 1);
	}
}