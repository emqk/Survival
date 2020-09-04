// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Inventory/ItemInstance.h"
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
	void ToggleInventory(const TArray<FItemInstance>& items);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenInventory(const TArray<FItemInstance>& items);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CloseInventory();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowInventoryItems(const TArray<FItemInstance>& items);

	//Interaction
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInteractionWorldActor(const AInteractableBase* actor);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInteractionWidgetLocation(const FVector& worldLocation);

	//Crew
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshNPCInfo(const UNPCData* npcData);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshCrew(const TArray<AAICharacter*>& crewMembers);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
