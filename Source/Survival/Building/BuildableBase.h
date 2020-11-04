// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../Interaction/InteractableBase.h"
#include "../Inventory/ItemInstance.h"
#include "BuildableBase.generated.h"

UCLASS()
class SURVIVAL_API ABuildableBase : public AInteractableBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly)
	UDestructibleComponent* defaultDestructibleComp = nullptr;
};
