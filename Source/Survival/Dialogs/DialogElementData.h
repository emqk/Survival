// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueEvent.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "DialogElementData.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FDialogElementData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDialogueEvent> dialogueEvent;
};
