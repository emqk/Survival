// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

UCLASS()
class SURVIVAL_API AInteractableBase : public AActor
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool InteractionTick(const float& deltaSeconds, const float& destructionSpeed, const float& buildSpeed);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float interactionDistance = 0.0f;

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* sceneComp;
};
