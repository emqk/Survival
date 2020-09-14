// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"


UCLASS()
class SURVIVAL_API AInteractableBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float interactionDistance = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool destroyOnSuccessfulInteraction = true;

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* sceneComp;
};
