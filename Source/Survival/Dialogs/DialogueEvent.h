// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
//#include "../PlayerGameMode.h"
#include "UObject/NoExportTypes.h"
#include "DialogueEvent.generated.h"

class APlayerGameMode;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SURVIVAL_API UDialogueEvent : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Execute();

protected:
	UFUNCTION(BlueprintPure)
	APlayerGameMode* GetMyGameMode() const;
};
