// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

UCLASS()
class SURVIVAL_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	FRotator GetRotationFromTime() const;

	UFUNCTION(BlueprintPure)
	FString GetFormattedTime() const;

protected:
	UPROPERTY(VisibleAnywhere)
	float worldTimeSpeed = 1;
	UPROPERTY(VisibleAnywhere)
	float elapsedTime = 90; //Each 90sec. of elapsed time is equal 6 hours
};
