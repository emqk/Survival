// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::Init(const float& dist, const bool& canBeInteracted)
{
	interactionDistanceBase = dist;
	canBeInteractedBase = canBeInteracted;
}

bool IInteractable::GetCanBeInteracted_Implementation() const
{
	return canBeInteractedBase;
}
