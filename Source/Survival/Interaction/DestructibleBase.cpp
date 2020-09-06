// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleBase.h"
#include "Kismet/KismetMathLibrary.h" 
#include "Kismet/GameplayStatics.h" 

ADestructibleBase::ADestructibleBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	staticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ADestructibleBase::BeginPlay()
{
	Super::BeginPlay();
	OnDestroyed.AddDynamic(this, &ADestructibleBase::WhenDestroyed);
}

void ADestructibleBase::WhenDestroyed(AActor* Act)
{
	UWorld* world = GetWorld();
	for (TSubclassOf<AActor> actor : afterDestroyActors)
	{
		world->SpawnActor<AActor>(actor, GetActorLocation(), FRotator(0, UKismetMathLibrary::RandomFloatInRange(0, 360), 0));
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), onDestroySound, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), onDestroyParticle, GetActorLocation());
}

// Called every frame
void ADestructibleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADestructibleBase::InteractionTick_Implementation(const float& deltaSeconds, const float& destructionSpeed, const float& buildSpeed)
{
	hp -= destructionSpeed * deltaSeconds;
	return hp <= 0;
}