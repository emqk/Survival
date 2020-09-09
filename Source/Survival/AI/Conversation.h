// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
#include "UObject/NoExportTypes.h"
#include "Conversation.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UConversation : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Init(const FVector& _location, AAICharacter* starting, AAICharacter* target);

	UFUNCTION()
	void Cleanup();

	UFUNCTION(BlueprintCallable)
	bool TickConversation(const float& deltaTime);

	UFUNCTION(BlueprintCallable)
	void AddCharacter(AAICharacter* character);
	UFUNCTION(BlueprintCallable)
	void RemoveCharacter(AAICharacter* character);

	UFUNCTION(BlueprintCallable)
	FVector GetLocation() const;

private:
	UFUNCTION()
	void DrawDebug() const;

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<AAICharacter*> characters;

private:
	FVector location;
	float radius = 300;

	const float endConversationThreshold = 20;
	const float socialNeedPerSec = 4.0f;
};