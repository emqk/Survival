// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Building/Architecture/Floor.h"
#include "GameFramework/Actor.h"
#include "BuildingManager.generated.h"

UCLASS()
class SURVIVAL_API ABuildingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BeginBuilding();

	UFUNCTION(BlueprintCallable)
	void TickBuilding(const FVector& mouseHit);

	UFUNCTION(BlueprintCallable)
	void EndBuilding(const FVector& mouseHit);

protected:
	UFUNCTION(BlueprintCallable)
	FIntVector TransformLocationToVectorIndex(const FVector& mouseHit) const;

private:
	UFUNCTION(BlueprintCallable)
	bool SetFloorAt(AFloor* floor, const FIntVector& vectorIndex);

	UFUNCTION(BlueprintCallable)
	bool IsVectorIndexValid(const FIntVector& vectorIndex) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AFloor> floorToBuild;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AFloor* currentFloor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundWave* buildSound;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int width;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int height;

	UPROPERTY(VisibleAnywhere)
	TArray<AFloor*> floors;

	float snapSize = 100;
};
