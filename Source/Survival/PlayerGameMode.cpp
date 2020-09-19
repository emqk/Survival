// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameMode.h"

AScavengeManager* APlayerGameMode::GetScavengeManager() const
{
	return scavengeManager;
}

AConversationManager* APlayerGameMode::GetConversationManager() const
{
	return conversationManager;
}

ABuildingManager* APlayerGameMode::GetBuildingManager() const
{
	return buildingManager;
}

AUIManager* APlayerGameMode::GetUIManager() const
{
	return uiManager;
}
