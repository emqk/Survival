// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "../Interaction/InteractableBase.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/ItemAssetAmountData.h"
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

	UFUNCTION(BlueprintCallable)
	void SetupCPP(UStaticMesh* staticMesh, UMaterialInterface* material, TSubclassOf<ABuildableBase> toBuildClass);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* myWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* inventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FItemAssetAmountData> buildRequirements;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float workAmountToBuild;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<ABuildableBase> toBuild;
};
