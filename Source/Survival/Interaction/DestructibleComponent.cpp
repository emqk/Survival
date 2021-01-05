// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "ItemActor.h"
#include "GameFramework/Actor.h"
#include "../PlayerGameMode.h"

// Sets default values for this component's properties
UDestructibleComponent::UDestructibleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDestructibleComponent::BeginPlay()
{
	Super::BeginPlay();

	startHP = hp;

	if (!onDestroyFX)
	{
		onDestroyFX = Cast<APlayerGameMode>(GetWorld()->GetAuthGameMode())->GetDefaultDestroyFX();
	}
}

// Called every frame
void UDestructibleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UDestructibleComponent::InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character)
{
	UE_LOG(LogTemp, Warning, TEXT("Destructible component interaction"));
	hp -= character->GetDestructionSpeedForMaterialType(materialType) * deltaSeconds;
	bool finished = hp <= 0;
	if (finished)
	{
		OnDestructed.Broadcast();
		GetOwner()->Destroy();
	}
	return finished;
}

void UDestructibleComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		//Spawn items
		UPlayerGameInstance* gameInstance = Cast<UPlayerGameInstance>(UGameplayStatics::GetGameInstance(this));
		gameInstance->itemManager->SpawnItemsFromActorInstance(afterDestroyActors, GetOwner()->GetActorLocation());

		//Play destroy sound and spawn particles
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), onDestroySound, GetOwner()->GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), onDestroyFX, GetOwner()->GetActorLocation());

		//Remove corresponding UI widget
		APlayerGameMode* gameMode = GetWorld()->GetAuthGameMode<APlayerGameMode>();
		gameMode->GetUIManager()->RemoveDestructionProgressWidget(this);
	}
}

float UDestructibleComponent::GetHPPercentageNormalized() const
{
	return hp / startHP;
}

void UDestructibleComponent::InitWidget()
{
	APlayerGameMode* gameMode = GetWorld()->GetAuthGameMode<APlayerGameMode>();
	gameMode->GetUIManager()->SetDestructionProgressWidget(this);
}
