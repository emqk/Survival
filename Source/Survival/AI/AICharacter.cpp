// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h" 
#include "Blueprint/AIBlueprintHelperLibrary.h" 
#include "BehaviorTree/BlackboardComponent.h" 
#include "../PlayerGameInstance.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	rightHandHandleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RHandHandle"));
	rightHandHandleMeshComponent->SetGenerateOverlapEvents(false);
	rightHandHandleMeshComponent->SetCollisionProfileName("NoCollision");
	rightHandHandleMeshComponent->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	rightHandHandleMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_rSocket"));

	inventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	AddOwnedComponent(inventoryComp);
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	data = NewObject<UNPCData>();
	Super::BeginPlay();

	Init(100, true);
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

void AAICharacter::SetInteraction(const FVector& location, AActor* actor, const EInteractionType& newInteractionType)
{
	UBlackboardComponent* blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
	blackboard->SetValueAsVector("TargetLocation", location);
	blackboard->SetValueAsObject("TargetActor", actor);
	interactionType = newInteractionType;
}

void AAICharacter::CancelCurrentInteraction()
{
	SetInteraction(GetActorLocation(), nullptr, EInteractionType::Default);
}

void AAICharacter::SimulateNeedsOverTime(const float& seconds)
{
	GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Hunger)->ChangeByAmount(hungerDecreasePerSec * seconds);
	GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Thirst)->ChangeByAmount(thirstDecreasePerSec * seconds);
	GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Energy)->ChangeByAmount(energyDecreasePerSec * seconds);
	GetNPCData()->GetNeeds()->GetNeedByType(NeedType::Social)->ChangeByAmount(-socialDecreasePerSec * seconds);
}

void AAICharacter::TickNeeds(const float& deltaTime)
{
	SimulateNeedsOverTime(deltaTime);
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

void AAICharacter::EquipVisuals(UStaticMesh* newMesh, const EquipType& equipType)
{
	if (equipType == EquipType::RightHand)
	{
		rightHandHandleMeshComponent->SetStaticMesh(newMesh);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't equip - i don't know that EquipType"))
	}
}

void AAICharacter::UnequipVisuals(const EquipType& equipType)
{
	if (equipType == EquipType::RightHand)
	{
		rightHandHandleMeshComponent->SetStaticMesh(nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't equip - i don't know that EquipType"))
	}
}

EInteractionType AAICharacter::GetInteractionType() const
{
	return interactionType;
}
