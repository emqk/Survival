// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "DestructibleMaterialType.h"
#include "../AI/AICharacter.h"
#include "NiagaraFunctionLibrary.h" 
#include "DestructibleComponent.generated.h"

class AItemActor;

USTRUCT(BlueprintType)
struct FItemActorInstance
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AItemActor> itemActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int amount = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestructed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_API UDestructibleComponent : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDestructibleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FOnDestructed OnDestructed;

	UFUNCTION(BlueprintPure)
	float GetHPPercentageNormalized() const;

protected:

	UFUNCTION(BlueprintCallable)
	void InitWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EDestructibleMaterialType materialType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundWave* onDestroySound;					 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onDestroyFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float startHP = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float hp = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FItemActorInstance> afterDestroyActors;
};
