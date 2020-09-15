// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointOfInterest.generated.h"

UCLASS()
class SURVIVAL_API APointOfInterest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointOfInterest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* root;
};
