// Fill out your copyright notice in the Description page of Project Settings.


#include "PointOfInterest.h"
#include "DrawDebugHelpers.h"

// Sets default values
APointOfInterest::APointOfInterest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	triggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerCylinder"));
	triggerMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Engine/BasicShapes/Cylinder"));
	if (CylinderAsset.Succeeded())
	{
		triggerMesh->SetStaticMesh(CylinderAsset.Object);
		triggerMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		float scaleAxis = radius / 100 * 2;
		triggerMesh->SetWorldScale3D(FVector(scaleAxis, scaleAxis, 1.0f));

		triggerMesh->SetGenerateOverlapEvents(true);
		triggerMesh->SetCollisionProfileName("OverlapAllDynamic");
		triggerMesh->OnComponentBeginOverlap.AddDynamic(this, &APointOfInterest::BeginOverlap);
		triggerMesh->OnComponentEndOverlap.AddDynamic(this, &APointOfInterest::EndOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find a mesh for cylinder!"))
	}
}

// Called when the game starts or when spawned
void APointOfInterest::BeginPlay()
{
	Super::BeginPlay();
	//Set trigger a proper scale
	float scaleAxis = radius / 100 * 2;
	triggerMesh->SetWorldScale3D(FVector(scaleAxis, scaleAxis, 1.0f));
}

// Called every frame
void APointOfInterest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugCylinder(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(0, 0, 100), radius, 20, FColor::Yellow, false, -1.0f, 0, 2);
}

bool APointOfInterest::ShouldTickIfViewportsOnly() const
{
	return true;
}

FVector APointOfInterest::GetRandomPointInRadius() const
{
	FVector location = FVector(FMath::FRandRange(-1, 1), FMath::FRandRange(-1, 1), 0) * (radius * 0.8f);
	return GetActorLocation() + location;
}

void APointOfInterest::OnBeginOverlap()
{
}

void APointOfInterest::OnEndOverlap()
{
}

void APointOfInterest::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAICharacter* character = Cast<AAICharacter>(OtherActor);
	if (character)
	{
		charactersIn.Add(character);
	}

	OnBeginOverlap();
}

void APointOfInterest::EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAICharacter* character = Cast<AAICharacter>(OtherActor);
	if (character)
	{
		charactersIn.Remove(character);
	}

	OnEndOverlap();
}
