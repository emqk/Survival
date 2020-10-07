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
	bool ConstructTick(const float& deltaTime, const float& buildSpeed, const float& destructionSpeed);

	UFUNCTION(BlueprintCallable)
	void GiveNeededItems(UInventoryComponent* inventory);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnOverlap();


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* myWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* inventoryComp;

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
