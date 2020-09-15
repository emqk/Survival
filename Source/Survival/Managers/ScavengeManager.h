// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Scavenge/ScavengeGroup.h"
#include "GameFramework/Actor.h"
#include "ScavengeManager.generated.h"

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
	void SetScavengePoints(AScavengePoint* wood);

	UFUNCTION(BlueprintCallable)
	void CreateScavengeGroup(const TArray<AAICharacter*>& characters, AScavengePoint* targetScavengePoint);

	UFUNCTION(BlueprintCallable)
	void SetWoodsInteractionPoint(AScavengePoint* point);
	UFUNCTION(BlueprintCallable)
	AScavengePoint* GetWoodsInteractionPoint() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	UPROPERTY(VisibleAnywhere)
	TArray<FScavengeGroup> scavengeGroups;

	UPROPERTY(VisibleAnywhere)
	AScavengePoint* woodsInteractionPoint;
};
