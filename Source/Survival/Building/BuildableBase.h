// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../Inventory/ItemInstance.h"
#include "BuildableBase.generated.h"

UCLASS()
class SURVIVAL_API ABuildableBase : public AActor
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

	UFUNCTION(BlueprintPure)
	float GetWorkAmountToBuild() const;
	UFUNCTION(BlueprintPure)
	const TArray<FItemInstance>& GetBuildRequirements() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* box;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FItemInstance> buildRequirements;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float workAmountToBuild;
};
