// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "../Inventory/ItemAmountData.h"
#include "../Inventory/ItemAssetAmountData.h"
#include "DestructibleBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API ADestructibleBase : public AInteractableBase
{
	GENERATED_BODY()

	ADestructibleBase();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void WhenDestroyed(AActor* Act);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool InteractionTick_Implementation(const float& deltaSeconds, const float& destructionSpeed, const float& buildSpeed) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* staticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnDestroy")
	USoundWave* onDestroySound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnDestroy")
	UParticleSystem* onDestroyParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float hp = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FItemAssetAmountData> afterDestroyItems;
};