// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AICharacter.h"
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

	UFUNCTION(BlueprintCallable)
	FVector GetRandomPointInRadius() const;


protected:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* root;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* triggerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float radius = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<AAICharacter*> charactersIn;

};
