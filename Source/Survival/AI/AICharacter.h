// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interaction/Interactable.h"
#include "../Inventory/InventoryComponent.h"
#include "../Interaction/DestructibleMaterialType.h"
#include "Statuses/NPCStatuses.h"
#include "NPCData.h"
#include "AICharacter.generated.h"

UCLASS()
class SURVIVAL_API AAICharacter : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	int GetID() const;

	UFUNCTION(BlueprintCallable)
	UNPCData* GetNPCData() const;

	UFUNCTION(BlueprintCallable)
	UNPCNeeds* GetNeeds() const;

	UFUNCTION(BlueprintCallable)
	UNPCStatuses* GetStatuses() const;

	UFUNCTION(BlueprintCallable)
	UNPCRelations* GetRelations() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetInteraction(const FVector& Location, AActor* Actor, const EInteractionType& newInteractionType, const EInteractionAnimationType& newInteractionAnimationType);

	UFUNCTION(BlueprintCallable)
	void CancelCurrentInteraction();

	UFUNCTION()
	void SimulateNeedsOverTime(const float& seconds);

	UFUNCTION()
	void TickNeeds(const float& deltaTime);

	UFUNCTION()
	void TickStatuses(const float& deltaTime);

	UFUNCTION(BlueprintCallable)
	void LookAtActor(AActor* actor);

	UFUNCTION(BlueprintCallable)
	void SetIsInteracting(const bool& newValue);

	UFUNCTION(BlueprintCallable)
	void SetIsTalking(const bool& newValue);
	UFUNCTION(BlueprintCallable)
	bool GetIsTalking() const;

	UFUNCTION(BlueprintCallable)
	float GetDestructionSpeedForMaterialType(const EDestructibleMaterialType& materialType) const;

	UFUNCTION(BlueprintCallable)
	float GetBuildSpeed() const;

	UFUNCTION(BlueprintCallable)
	bool CanBeSelected() const;

	UFUNCTION(BlueprintCallable)
	bool IsEnabled() const;

	UFUNCTION(BlueprintCallable)
	void SetMeActive(const bool& value);

	UFUNCTION(BlueprintCallable)
	void EquipVisuals(UStaticMesh* newMesh, const EquipType& equipType);

	UFUNCTION(BlueprintCallable)
	void UnequipVisuals(const EquipType& equipType);

	UFUNCTION(BlueprintCallable)
	EInteractionType GetInteractionType() const;

	UFUNCTION(BlueprintCallable)
	EInteractionAnimationType GetInteractionAnimationType() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* inventoryComp;

protected:
	UPROPERTY(EditDefaultsOnly)
	FName righthandSocketName = "hand_R_endSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* rightHandHandleMeshComponent;

	UPROPERTY(VisibleAnywhere)
	EInteractionType interactionType;

	UPROPERTY(VisibleAnywhere)
	EInteractionAnimationType interactionAnimationType;

	UPROPERTY(EditDefaultsOnly)
	float destructionSpeed = 1;

	UPROPERTY(EditDefaultsOnly)
	float buildSpeed = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isInteracting = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float lookAtInteractActorDist = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isTalking = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isThisActorEnabled = true;

	UPROPERTY(EditAnywhere)
	UNPCData* data;

	UPROPERTY()
	UNPCNeeds* myNeeds = nullptr;

	UPROPERTY()
	UNPCStatuses* myStatuses = nullptr;

	UPROPERTY()
	UNPCRelations* myRelations = nullptr;

private:
	const float hungerDecreasePerSec = 0.7f;
	const float thirstDecreasePerSec = 1.1f;
	const float energyDecreasePerSec = 0.3f;
	const float socialDecreasePerSec = 0.14f;
	const float happynessDecreasePerSec = 0.08f;
};