// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInstance.h"
#include "ItemAmountData.h"
#include "EquipType.h"
#include "InventoryComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool MoveItemByID(const FName& itemID, UInventoryComponent* targetInventory, const int& amount = -1);
	UFUNCTION(BlueprintCallable)
	bool MoveItemByIndex(const int& itemIndex, UInventoryComponent* targetInventory, const int& amount = -1);
	UFUNCTION(BlueprintCallable)
	bool MoveAllItems(UInventoryComponent* targetInventory);

	UFUNCTION(BlueprintCallable)
	bool AddItemsFromAsset(const TArray<FItemInstance>& itemsToAdd);
	UFUNCTION(BlueprintCallable)
	bool AddItem(const FItemInstance& item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(const int32& index, const int32& amount = -1);
	UFUNCTION(BlueprintCallable)
	bool RemoveItemOfID(const FName& itemID, const int& amount);
	UFUNCTION(BlueprintCallable)
	bool RemoveItemOfIDMax(const FName& itemID);
	UFUNCTION(BlueprintCallable)
	bool RemoveItems(const TArray<FItemInstance>& itemsToRemove);
	UFUNCTION(BlueprintCallable)
	void RemoveAllItems();

	UFUNCTION(BlueprintCallable)
	bool UseItemOfIndex(const int& index);
	UFUNCTION(BlueprintCallable)
	bool DropItemOfIndex(const int& index);
	UFUNCTION(BlueprintCallable)
	void DropAllItems();

	UFUNCTION(BlueprintCallable)
	bool UnequipItem(const EquipType& equipType);
	UFUNCTION(BlueprintCallable)
	UItemDataAsset* GetEquipedItem(const EquipType& equipType) const;

	UFUNCTION(BlueprintCallable)
	bool HaveAmountOfItem(const FName& itemID, const int& amount) const;
	UFUNCTION(BlueprintCallable)
	bool HaveAmountOfItems(const TArray<FItemInstance>& neededItems) const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetAmountOfItem(const FName& itemID) const;
	UFUNCTION(BlueprintCallable)
	int GetItemIndex(const FName& itemID) const;
	UFUNCTION(BlueprintCallable)
	const TArray<FItemInstance>& GetItems() const;

	UFUNCTION(BlueprintCallable)
	float CalculateItemsCost() const;

	UFUNCTION()
	void CalculateWeightAndSpace();

	//Weight
	UFUNCTION(BlueprintPure)
	float GetCurrentWeight() const;
	UFUNCTION(BlueprintPure)
	float GetMaxWeight() const;

	//Space
	UFUNCTION(BlueprintPure)
	float GetCurrentSpace() const;
	UFUNCTION(BlueprintPure)
	float GetMaxSpace() const;

protected:
	UFUNCTION()
	void RefreshUI();

	UPROPERTY(VisibleAnywhere)
	TArray<FItemInstance> items;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<EquipType, UItemDataAsset*> equipment;

	
	UPROPERTY(VisibleAnywhere)
	float maxWeight = 10;
	UPROPERTY(VisibleAnywhere)
	float currentWeight = 0;

	UPROPERTY(VisibleAnywhere)
	float maxSpace = 10;
	UPROPERTY(VisibleAnywhere)
	float currentSpace = 0;
};