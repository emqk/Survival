// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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

	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UDestructibleComponent::InitWidget, 0.1f, false);
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
	UWorld* world = GetWorld();
	for (TSubclassOf<AActor> actor : afterDestroyActors)
	{
		world->SpawnActor<AActor>(actor, GetOwner()->GetActorLocation(), FRotator(0, UKismetMathLibrary::RandomFloatInRange(0, 360), 0));
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), onDestroySound, GetOwner()->GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), onDestroyParticle, GetOwner()->GetActorLocation());
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
