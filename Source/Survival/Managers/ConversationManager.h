// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/Conversation.h"
#include "GameFramework/Actor.h"
#include "ConversationManager.generated.h"

UCLASS()
class SURVIVAL_API AConversationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConversationManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartConversation(AAICharacter* starting, AAICharacter* target);

	UFUNCTION(BlueprintCallable)
	UConversation* FindExistingConversationForLocation(const FVector& location) const;

	UFUNCTION(BlueprintCallable)
	UConversation* GetConversation(const AAICharacter* character) const;

private:
	UFUNCTION()
	void TickConversations(const float& deltaTime);

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UConversation*> conversations;
};