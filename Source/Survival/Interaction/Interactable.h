// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class SURVIVAL_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool InteractionTick(const float& deltaSeconds, const AAICharacter* character);

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init(const float& dist, const bool& destroyOnSuccess);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetDestroyOnSuccessInteraction() const;
	bool GetDestroyOnSuccessInteraction_Implementation() const;

	float interactionDistance = 50.0f;
	bool destroyOnSuccessfulInteraction = true;
};