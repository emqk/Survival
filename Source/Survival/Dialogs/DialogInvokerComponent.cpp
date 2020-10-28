// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogInvokerComponent.h"
#include "../Managers/DialogManager.h"
#include "../PlayerGameMode.h"

// Sets default values for this component's properties
UDialogInvokerComponent::UDialogInvokerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogInvokerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDialogInvokerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogInvokerComponent::StartDialog(AAICharacter* startedBy)
{
	APlayerGameMode* gameMode = GetWorld()->GetAuthGameMode<APlayerGameMode>();
	if (gameMode)
	{
		gameMode->GetDialogManager()->StartDialog(this, startedBy);
	}
}

void UDialogInvokerComponent::SetAnswerTime(const float& timeToAnswer)
{
	dialogData->timeToAnswer = timeToAnswer;
}

UDialogData* UDialogInvokerComponent::GetDialogData() const
{
	return dialogData;
}
