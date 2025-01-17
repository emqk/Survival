// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogManager.h"
#include "UIManager.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerGameMode.h"

// Sets default values
ADialogManager::ADialogManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADialogManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDialogStarted)
	{
		currentTimeToEnd -= DeltaTime;

		if (currentTimeToEnd <= 0)
		{
			EndDialog();
		}
	}
}

void ADialogManager::StartDialog(UDialogInvokerComponent* invoker, AAICharacter* startedBy)
{
	if (!invoker)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't start dialog! - Invoker is null!"))
	}

	APlayerGameMode* gameMode = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode)
	{
		lastDialogueStartedBy = startedBy;
		lastDialogueInvoker = invoker;

		UDialogData* dialogData = invoker->GetDialogData();
		gameMode->GetUIManager()->OpenDialogPanel(dialogData);
		isDialogStarted = true;
		maxTimeToEnd = dialogData->timeToAnswer;
		currentTimeToEnd = maxTimeToEnd;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't start dialog! - Can't cast gameMode!"))
	}
}

void ADialogManager::EndDialog()
{
	APlayerGameMode* gameMode = GetWorld()->GetAuthGameMode<APlayerGameMode>();
	if (gameMode)
	{
		gameMode->GetUIManager()->CloseDialogPanel();
		isDialogStarted = false;
		UE_LOG(LogTemp, Warning, TEXT("Dialog ended!"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't end dialog! - Can't cast gameMode!"))
	}

}
