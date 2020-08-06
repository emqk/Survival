// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInstance.h"
#include "ItemAmountData.h"
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
	bool MoveItem(const FName& itemID, const int& amount, UInventoryComponent* targetInventory);

	UFUNCTION(BlueprintCallable)
	void AddItemsFromAsset(const TArray<FItemInstance>& itemsToAdd);
	UFUNCTION(BlueprintCallable)
	void AddItem(const FItemInstance& item);
	UFUNCTION(BlueprintCallable)
	bool RemoveItemOfID(const FName& itemID, const int& amount);
	UFUNCTION(BlueprintCallable)
	bool RemoveItemOfIDMax(const FName& itemID);

	UFUNCTION(BlueprintCallable)
	bool HaveAmountOfItem(const FName& itemID, const int& amount) const;
	UFUNCTION(BlueprintCallable)
	bool HaveAmountOfItems(const TArray<FItemInstance>& neededItems) const;
	UFUNCTION(BlueprintCallable)
	int GetItemIndex(const FName& itemID) const;
	UFUNCTION(BlueprintCallable)
	const TArray<FItemInstance>& GetItems() const;

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<FItemInstance> items;
};
