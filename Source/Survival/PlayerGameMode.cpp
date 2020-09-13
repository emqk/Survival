// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameMode.h"

AConversationManager* APlayerGameMode::GetConversationManager() const
{
	return conversationManager;
}

ABuildingManager* APlayerGameMode::GetBuildingManager() const
{
	return buildingManager;
}
