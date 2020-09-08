// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::Init(const float& dist, bool& destroyOnSuccess)
{
	interactionDistance = dist;
	destroyOnSuccessfulInteraction = destroyOnSuccess;
}

bool IInteractable::GetDestroyOnSuccessInteraction_Implementation() const
{
	return destroyOnSuccessfulInteraction;
}