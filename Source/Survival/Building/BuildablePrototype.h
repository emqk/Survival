// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
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

	UFUNCTION(BlueprintCallable)
	bool CanBePlaced() const;

protected:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshText();

	UFUNCTION(BlueprintCallable)
	void SetupVisuals(TSubclassOf<ABuildableBase> toBuildClass);

	UFUNCTION(BlueprintCallable)
	void GiveNeededItems(UInventoryComponent* inventory);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* myWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* inventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FItemInstance> buildRequirements;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float workAmountToBuild;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<ABuildableBase> toBuild;

	UPROPERTY(VisibleAnywhere)
	bool isOverlapping = false;
};
