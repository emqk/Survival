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

	UFUNCTION(BlueprintCallable)
	void AddCharacter(AAICharacter* character);
	UFUNCTION(BlueprintCallable)
	void RemoveCharacter(AAICharacter* character);

	UFUNCTION(BlueprintCallable)
	FVector GetLocation() const;

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<AAICharacter*> characters;

	FVector location;
};
