// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogData.h"
#include "DialogInvokerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_API UDialogInvokerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogInvokerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void StartDialog();

	UFUNCTION(BlueprintCallable)
	void SetAnswerTime(const float& timeToAnswer);

	const FDialogData& GetAnswers() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDialogData answers;
};
