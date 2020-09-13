// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Building/Architecture/Floor.h"
#include "../Building/Architecture/Wall.h"
#include "../Building/BuildableBase.h"
#include "../Building/BuildablePrototype.h"
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
	void BeginBuilding(TSubclassOf<ABuildableBase> buildable, ABuildablePrototype* prototype);

	UFUNCTION(BlueprintCallable)
	void TickBuilding(const FVector& mouseHit);

	UFUNCTION(BlueprintCallable)
	void EndBuilding();

	UFUNCTION(BlueprintCallable)
	void CancelBuilding();

	UFUNCTION(BlueprintCallable)
	FVector TransformToSnap(const FVector& mouseHit) const;

	UFUNCTION(BlueprintCallable)
	void ChangeRotationY(const float& amount);

	UFUNCTION(BlueprintCallable)
	bool IsBuilding() const;

protected:
	UFUNCTION(BlueprintCallable)
	FIntVector TransformLocationToVectorIndex(const FVector& mouseHit) const;

private:
	UFUNCTION(BlueprintCallable)
	bool SetFloorAt(AFloor* floor, const FIntVector& vectorIndex);

	UFUNCTION(BlueprintCallable)
	bool SetWallAt(AWall* wall, const FIntVector& vectorIndex);

	UFUNCTION(BlueprintCallable)
	bool IsVectorIndexValid(const FIntVector& vectorIndex) const;

	UFUNCTION(BlueprintCallable)
	bool IsWallVectorIndexValid(const FIntVector& vectorIndex) const;

protected:
	//Floor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AFloor> floorToBuild;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<AFloor> currentFloor;

	//Wall
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AWall> wallToBuild;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<AWall> currentWall;

	//Buildable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<ABuildableBase> currentBuildable;

	//Build control
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABuildablePrototype* currentPrototype;

	//Sounds
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundWave* buildSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundWave* cancelBuildingSound;

	//Other
	UPROPERTY(EditDefaultsOnly)
	FName afterPlacingProtCollisionProfile = "OverlapAll";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int width;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int height;

	UPROPERTY(VisibleAnywhere)
	float currentRotationY = 0;


	UPROPERTY(VisibleAnywhere)
	TArray<AFloor*> floors;
	UPROPERTY(VisibleAnywhere)
	TArray<AWall*> walls;

	const float snapSize = 100;
};
