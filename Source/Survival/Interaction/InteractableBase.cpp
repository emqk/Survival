// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(sceneComp);
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	Init(interactionDistance, canBeInteracted, interactionAnimationType);
	UActorComponent* actorComp = GetComponentByClass(UDestructibleComponent::StaticClass());
	if (actorComp)
		destructibleComp = Cast<UDestructibleComponent>(actorComp);
}

bool AInteractableBase::DestructionInteraction(const float& deltaSeconds, const AAICharacter* character)
{
	UE_LOG(LogTemp, Warning, TEXT("DestructionInteraction"));

	if (destructibleComp)
	{
		return IInteractable::Execute_InteractionTick(destructibleComp, deltaSeconds, character);
	}
	
	return false;
}

bool AInteractableBase::InteractionTick_Implementation(const float& deltaSeconds, const AAICharacter* character)
{
	UE_LOG(LogTemp, Warning, TEXT("BASE_INTERACTION"));
	return true;
}
