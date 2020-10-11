// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::Init(const float& dist, const bool& canBeInteracted, const EInteractionAnimationType& _interactionAnimationType)
{
	interactionDistanceBase = dist;
	canBeInteractedBase = canBeInteracted;
	interactionAnimationType = _interactionAnimationType;
}

bool IInteractable::GetCanBeInteracted_Implementation() const
{
	return canBeInteractedBase;
}

EInteractionAnimationType IInteractable::GetAnimType_Implementation() const
{
	return interactionAnimationType;
}
