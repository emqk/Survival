// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interaction/Interactable.h"
#include "../Inventory/InventoryComponent.h"
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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInteraction(const FVector& Location, const AActor* Actor);

	UFUNCTION()
	void TickNeeds(const float& deltaTime);

	UFUNCTION(BlueprintCallable)
	void LookAtActor(AActor* actor);

	UFUNCTION(BlueprintCallable)
	void SetIsInteracting(const bool& newValue);

	UFUNCTION(BlueprintCallable)
	void SetIsTalking(const bool& newValue);
	UFUNCTION(BlueprintCallable)
	bool GetIsTalking() const;

	UFUNCTION(BlueprintCallable)
	float GetDestructionSpeed() const;

	UFUNCTION(BlueprintCallable)
	float GetBuildSpeed() const;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* inventoryComp;

protected:
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

	UPROPERTY(EditAnywhere)
	UNPCData* data;

private:
	const float hungerDecreasePerSec = 0.7f;
	const float thirstDecreasePerSec = 1.1f;
	const float energyDecreasePerSec = 0.3f;
	const float socialDecreasePerSec = 0.04f;
};