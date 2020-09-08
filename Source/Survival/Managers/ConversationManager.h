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

private:
	UFUNCTION()
	void DebugDraw() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartConversation(AAICharacter* starting, AAICharacter* target);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UConversation*> conversations;
};