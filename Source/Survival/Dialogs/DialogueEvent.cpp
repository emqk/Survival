// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueEvent.h"
#include "../PlayerGameMode.h"

APlayerGameMode* UDialogueEvent::GetMyGameMode()
{
	return Cast<APlayerGameMode>(GetWorld()->GetAuthGameMode());
}
