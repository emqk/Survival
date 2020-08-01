// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../AI/AICharacter.h"
#include "CrewManager.generated.h"

UCLASS()
class SURVIVAL_API ACrewManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrewManager();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddMember(AAICharacter* member);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveMember(AAICharacter* member);

	UFUNCTION(BlueprintCallable)
	FName GetRandomName(const TArray<FName>& names);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <AAICharacter*> members;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> availableNames;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> availableSurnames;
};
