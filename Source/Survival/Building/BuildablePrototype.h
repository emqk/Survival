// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "../Interaction/InteractableBase.h"
#include "../Inventory/InventoryComponent.h"
#include "BuildableBase.h"
#include "BuildablePrototype.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API ABuildablePrototype : public AInteractableBase
{
	GENERATED_BODY()

public:
	ABuildablePrototype();


protected:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshText();

	UFUNCTION(BlueprintCallable)
	void SetupVisuals(UStaticMesh* staticMesh, UMaterialInterface* material, TSubclassOf<ABuildableBase> toBuildClass);

	UFUNCTION(BlueprintCallable)
	void GiveNeededItems(UInventoryComponent* inventory);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* myWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* inventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FItemInstance> buildRequirements;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float workAmountToBuild;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<ABuildableBase> toBuild;
};
