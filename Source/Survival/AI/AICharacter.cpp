// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h" 
#include "Blueprint/AIBlueprintHelperLibrary.h" 
#include "BehaviorTree/BlackboardComponent.h" 
#include "../PlayerGameInstance.h"
#include "../PlayerGameMode.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rightHandHandleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RHandHandle"));
	rightHandHandleMeshComponent->SetGenerateOverlapEvents(false);
	rightHandHandleMeshComponent->SetCollisionProfileName("NoCollision");
	rightHandHandleMeshComponent->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	rightHandHandleMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, righthandSocketName);

	inventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	AddOwnedComponent(inventoryComp);
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	//data = NewObject<UNPCData>();
	myNeeds = NewObject<UNPCNeeds>();
	myStatuses = NewObject<UNPCStatuses>();
	myRelations = NewObject<UNPCRelations>();
	Super::BeginPlay();

	Init(100, true, EInteractionAnimationType::Default);
}

int AAICharacter::GetID() const
{
	return GetUniqueID();
}

UNPCData* AAICharacter::GetNPCData() const
{
	if (data != nullptr)
	{
		return data;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NPCData Asset is null!"));
		return nullptr;
	}
}

UNPCNeeds* AAICharacter::GetNeeds() const
{
	return myNeeds;
}

UNPCStatuses* AAICharacter::GetStatuses() const
{
	return myStatuses;
}

UNPCRelations* AAICharacter::GetRelations() const
{
	return myRelations;
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickNeeds(DeltaTime);
	TickStatuses(DeltaTime);
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::SetInteraction(const FVector& location, AActor* actor, const EInteractionType& newInteractionType, const EInteractionAnimationType& newInteractionAnimationType)
{
	UBlackboardComponent* blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
	blackboard->SetValueAsVector("TargetLocation", location);
	blackboard->SetValueAsObject("TargetActor", actor);
	interactionType = newInteractionType;

	//Always use destruction animation when the target is to destroy target actor
	if (newInteractionType == EInteractionType::Destruction)
	{
		interactionAnimationType = EInteractionAnimationType::Default;
	}
	else
	{
		interactionAnimationType = newInteractionAnimationType;
	}

}

void AAICharacter::CancelCurrentInteraction()
{
	SetInteraction(GetActorLocation(), nullptr, EInteractionType::Default, EInteractionAnimationType::Default);
}

void AAICharacter::SimulateNeedsOverTime(const float& seconds)
{
	if (GetNPCData())
	{
		GetNeeds()->GetNeedByType(NeedType::Hunger)->ChangeByAmount(hungerDecreasePerSec * seconds);
		GetNeeds()->GetNeedByType(NeedType::Hydration)->ChangeByAmount(thirstDecreasePerSec * seconds);
		GetNeeds()->GetNeedByType(NeedType::Energy)->ChangeByAmount(energyDecreasePerSec * seconds);
		GetNeeds()->GetNeedByType(NeedType::Social)->ChangeByAmount(-socialDecreasePerSec * seconds);
		GetNeeds()->GetNeedByType(NeedType::Happyness)->ChangeByAmount(-happynessDecreasePerSec * seconds);

		//Die
		if (GetNeeds()->GetNeedByType(NeedType::Health)->GetAmount() <= 0)
		{
			Die();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't tick needs - Can't get NPC Data!"))
	}
}

void AAICharacter::TickNeeds(const float& deltaTime)
{
	SimulateNeedsOverTime(deltaTime);
}

void AAICharacter::TickStatuses(const float& deltaTime)
{
	if (GetNPCData())
	{
		GetStatuses()->TickStatuses(GetNeeds(), deltaTime);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't tick statuses - Can't get NPC Data!"))
	}
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

float AAICharacter::GetDestructionSpeedForMaterialType(const EDestructibleMaterialType& materialType) const
{
	if (inventoryComp)
	{
		UItemDataAsset* equipedItem = inventoryComp->GetEquipedItem(EquipType::RightHand);
		if (equipedItem && equipedItem->destructMaterialType == materialType)
		{
			return destructionSpeed * equipedItem->destructionSpeedMultiplier;
		}
	}

	return destructionSpeed;
}

float AAICharacter::GetBuildSpeed() const
{
	return buildSpeed;
}

bool AAICharacter::CanBeSelected() const
{
	APlayerGameMode* gameMode = GetWorld()->GetAuthGameMode<APlayerGameMode>();
	AScavengeManager* scavengeManager = gameMode->GetScavengeManager();

	bool result = !scavengeManager->IsNPCInAnyScavengeGroup(this);

	return result;
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

EInteractionAnimationType AAICharacter::GetInteractionAnimationType() const
{
	return interactionAnimationType;
}

void AAICharacter::Die()
{
	inventoryComp->DropAllItems();
	Destroy();
}
