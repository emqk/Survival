// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Inventory/InventoryComponent.h"
#include "../Interaction/DestructibleBase.h"
#include "NPCData.h"
#include "AICharacter.generated.h"


UCLASS()
class SURVIVAL_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	UNPCData* GetNPCData() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void LookAtActor(AActor* actor);

	UFUNCTION(BlueprintCallable)
	void SetIsInteracting(const bool& newValue);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* inventoryComp;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float destructionSpeed = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float buildSpeed = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isInteracting = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float lookAtInteractActorDist = 50;

	UPROPERTY(EditAnywhere)
	UNPCData* data;
};