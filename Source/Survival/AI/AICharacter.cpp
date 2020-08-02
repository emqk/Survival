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

	data = NewObject<UNPCData>();
	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

UNPCData* AAICharacter::GetNPCData() const
{
	return data;
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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