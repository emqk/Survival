// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NiagaraFunctionLibrary.h" 
#include "Managers/ScavengeManager.h"
#include "Managers/BuildingManager.h"
#include "Managers/ConversationManager.h"
#include "Managers/DialogManager.h"
#include "Managers/CrewManager.h"
#include "Managers/UIManager.h"
#include "Managers/TimeManager.h"
#include "PlayerGameMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin = "true"))
class SURVIVAL_API APlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    //Get managers
    UFUNCTION(BlueprintCallable)
    AScavengeManager* GetScavengeManager() const;
    UFUNCTION(BlueprintCallable)
    AConversationManager* GetConversationManager() const;
    UFUNCTION(BlueprintCallable)
    ADialogManager* GetDialogManager() const;
    UFUNCTION(BlueprintCallable)
    ABuildingManager* GetBuildingManager() const;
    UFUNCTION(BlueprintCallable)
    AUIManager* GetUIManager() const;
    UFUNCTION(BlueprintCallable)
    ATimeManager* GetTimeManager() const;

    //Get defaults
    UFUNCTION(BlueprintCallable)
    UNiagaraSystem* GetDefaultDestroyFX() const;

protected:
    //Managers
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ABuildingManager* buildingManager = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AScavengeManager* scavengeManager = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AConversationManager* conversationManager = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ADialogManager* dialogManager = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ACrewManager* crewManager = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AUIManager* uiManager = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ATimeManager* timeManager = nullptr;


    //Defaults
    UPROPERTY(EditDefaultsOnly)
    UNiagaraSystem* defaultDestroyFX;
};
