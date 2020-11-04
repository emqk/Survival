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

	virtual bool InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character) override;

	UFUNCTION(BlueprintCallable)
	void Setup();

	UFUNCTION(BlueprintCallable)
	void Build();

	UFUNCTION(BlueprintPure)
	float GetWorkAmountToBuild() const;
	UFUNCTION(BlueprintPure)
	const TArray<FItemInstance>& GetBuildRequirements() const;

	UFUNCTION(BlueprintPure)
	bool HaveRequiredItems() const;

	UFUNCTION(BlueprintPure)
	bool CanBePlaced() const;


	UFUNCTION(BlueprintCallable)
	void CancelBuilding();

protected:

	UFUNCTION(BlueprintCallable)
	void RefreshText();

	UFUNCTION()
	bool ConstructTick(const float& deltaTime, const float& buildSpeed);

	UFUNCTION(BlueprintCallable)
	void GiveNeededItems(UInventoryComponent* inventory);

	UFUNCTION()
	void OnOverlapBegin(class AActor* ThisActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* ThisActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlap();


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* myWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* inventoryComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FItemInstance> buildRequirements;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float workAmountToBuild;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ABuildableBase> toBuild;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundWave* finishBuildSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float currentWorkAmount;

	UPROPERTY(VisibleAnywhere)
	bool isOverlapping = false;
};
