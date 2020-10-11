// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"


UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Default, Destruction
};

UENUM(BlueprintType)
enum class EInteractionAnimationType : uint8
{
	Default, Sleep
};

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

	void Init(const float& dist, const bool& canBeInteracted, const EInteractionAnimationType& _interactionAnimationType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool InteractionTick(const float& deltaSeconds, const AAICharacter* character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetCanBeInteracted() const;
	bool GetCanBeInteracted_Implementation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EInteractionAnimationType GetAnimType() const;
	EInteractionAnimationType GetAnimType_Implementation() const;

	float interactionDistanceBase = 50.0f;
	bool canBeInteractedBase = true;
	EInteractionAnimationType interactionAnimationType;
};