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

void UDialogInvokerComponent::StartDialog()
{
	APlayerGameMode* gameMode = GetWorld()->GetAuthGameMode<APlayerGameMode>();
	if (gameMode)
	{
		gameMode->GetDialogManager()->StartDialog(this);
	}
}

void UDialogInvokerComponent::AddAnswer(const FDialogElementData& dialogAnswer)
{
	answers.dialogElements.Add(dialogAnswer);
}

const FDialogData& UDialogInvokerComponent::GetAnswers() const
{
	return answers;
}
