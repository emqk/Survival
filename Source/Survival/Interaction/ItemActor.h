// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Inventory/ItemInstance.h"
#include "../Interaction/InteractableBase.h"
#include "../AI/AICharacter.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API AItemActor : public AInteractableBase
{
	GENERATED_BODY()
	
public:
	AItemActor();

	UFUNCTION(BlueprintCallable)
	void InitItemsAfterCollect(const FItemInstance& item);

	virtual void Tick(float DeltaTime) override;

	virtual bool InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character) override;

	UStaticMesh* GetMesh() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FItemInstance afterCollectItem;

};