// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interaction/ScavengePoint.h"
#include "../Scavenge/ScavengeGroup.h"
#include "GameFramework/Actor.h"
#include "ScavengeManager.generated.h"


USTRUCT(BlueprintType)
struct FItemsRandomizeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemDataAsset* itemToGet;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int itemAmountMin;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int itemAmountMax;
};

USTRUCT(BlueprintType)
struct FScavengeItems
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FItemsRandomizeData> items;
};

UCLASS()
class SURVIVAL_API AScavengeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScavengeManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetScavengePoints();

	UFUNCTION(BlueprintCallable)
	bool CreateScavengeGroup(const TArray<AAICharacter*>& characters, AScavengePoint* targetScavengePoint, const ScavengeType& scavengeType);

	UFUNCTION(BlueprintCallable)
	bool IsNPCInAnyScavengeGroup(const AAICharacter* character) const;

	UFUNCTION()
	void CheckAllScavengePoints();

	UFUNCTION(BlueprintCallable)
	bool CheckScavengePoint(AScavengePoint* scavengePoint);

	UFUNCTION(BlueprintCallable)
	AScavengePoint* GetRandomScavengePoint() const;

	UFUNCTION(BlueprintCallable)
	AScavengePoint* GetScavengePoint(const int& index) const;

	UFUNCTION(BlueprintCallable)
	bool CancelScavengeGroupAtIndex(const int& index);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void TickScavengeGroups(const float& deltaTime);

	UFUNCTION()
	void EndScavengeGroup(FScavengeGroup& scavengeGroup, const int& index, const bool& cancel = false);


	UFUNCTION()
	TArray<FItemInstance> GenerateItemsFromScavenge(const ScavengeType& scavengeType) const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FScavengeGroup> scavengeGroups;

	UPROPERTY(VisibleAnywhere)
	TArray<AScavengePoint*> scavengePoints;

	UPROPERTY(EditDefaultsOnly)
	TMap<ScavengeType, FScavengeItems> itemsFromScavenge;
};
