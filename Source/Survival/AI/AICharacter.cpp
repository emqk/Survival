// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h" 
#include "../PlayerGameInstance.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	inventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	AddOwnedComponent(inventoryComp);
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	data = NewObject<UNPCData>();
	Super::BeginPlay();

	bool destrAfterInteract = false;
	Init(100, destrAfterInteract);
}

int AAICharacter::GetID() const
{
	return GetUniqueID();
}

UNPCData* AAICharacter::GetNPCData() const
{
	return data;
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickNeeds(DeltaTime);
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::TickNeeds(const float& deltaTime)
{
	GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Hunger)->ChangeByAmount(hungerDecreasePerSec * deltaTime);
	GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Thirst)->ChangeByAmount(thirstDecreasePerSec * deltaTime);
	GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Energy)->ChangeByAmount(energyDecreasePerSec * deltaTime);
	GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Social)->ChangeByAmount(-socialDecreasePerSec * deltaTime);
}

void AAICharacter::LookAtActor(AActor* actor)
{
	if (IsValid(actor))
	{
		FRotator lookRotation = FRotator(0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), actor->GetActorLocation()).Yaw, 0);
		SetActorRotation(lookRotation);
	}
}

void AAICharacter::SetIsInteracting(const bool& newValue)
{
	isInteracting = newValue;
}

void AAICharacter::SetIsTalking(const bool& newValue)
{
	isTalking = newValue;
}

bool AAICharacter::GetIsTalking() const
{
	return isTalking;
}

float AAICharacter::GetDestructionSpeed() const
{
	return destructionSpeed;
}

float AAICharacter::GetBuildSpeed() const
{
	return buildSpeed;
}

bool AAICharacter::IsEnabled() const
{
	return isThisActorEnabled;
}

void AAICharacter::SetMeActive(const bool& value)
{
	if (value)
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		SetActorTickEnabled(true);
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
	}

	isThisActorEnabled = value;
}
