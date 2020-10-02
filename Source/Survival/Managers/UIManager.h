// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Inventory/InventoryComponent.h"
#include "../Interaction/InteractableBase.h"
#include "../AI/AICharacter.h"
#include "UIManager.generated.h"

UCLASS()
class SURVIVAL_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();

	//Inventory
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleInventory(UInventoryComponent* inventory);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenInventory(UInventoryComponent* inventory);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseInventory();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowInventoryItems(UInventoryComponent* inventory);

	//Interaction
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInteractionWorldActor(const AActor* actor);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInteractionWidgetLocation(const FVector& worldLocation);

	//Crew
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshNPCInfo(const AAICharacter* aiCharacter);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshCrew(const TArray<AAICharacter*>& crewMembers);

	//Scavenge
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleScavengePanel();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenScavengePanel();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseScavengePanel();

	//Dialog
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenDialogPanel(const TArray<FText>& answers);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseDialogPanel();

	//Settings
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleSettingsPanel();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenSettingsPanel();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseSettingsPanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
