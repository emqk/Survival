// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Dialogs/DialogInvokerComponent.h"
#include "DialogManager.generated.h"

UCLASS()
class SURVIVAL_API ADialogManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void StartDialog(UDialogInvokerComponent* invoker, AAICharacter* startedBy);
	UFUNCTION(BlueprintCallable)
	void EndDialog();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AAICharacter* lastDialogueStartedBy = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDialogInvokerComponent* lastDialogueInvoker = nullptr;

	bool isDialogStarted = false;
	UPROPERTY(BlueprintReadOnly)
	float currentTimeToEnd = 0;
	UPROPERTY(BlueprintReadOnly)
	float maxTimeToEnd = 0;
};
