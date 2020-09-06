// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralTerrain.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include <SimplexNoise\Public\SimplexNoiseBPLibrary.h>

// Sets default values
AProceduralTerrain::AProceduralTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	mesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProceduralTerrain::BeginPlay()
{
	Super::BeginPlay();
	Generate();
}

// Called every frame
void AProceduralTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProceduralTerrain::Generate()
{
	double start = FPlatformTime::Seconds();

	ClearMeshData();

	GenerateVertices();
	FillMesh();
	//CalculateNormals();
	mesh->SetMaterial(0, material);

	//normals.Init(FVector(0.0f, 0.0f, 1.0f), vertices.Num());
	vertexColors.Init(FColor(0.0f, 0.0f, 0.0f, 1.0f), 3);
	tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);

	mesh->CreateMeshSection(0, vertices, triangles, normals, uvs, vertexColors, tangents, true);
	
	GenerateVegetation();

	AlignNavMeshToTerrain();

	double end = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Warning, TEXT("Terrain generated in: %f s. | Tris: %u"), end - start, triangles.Num()/3);
}

void AProceduralTerrain::GenerateVegetation()
{
	FVector terrainLocation = GetActorLocation();
	UWorld* world = GetWorld();
	for (size_t i = 0; i < vegetationToSpawn.Num(); i++)
	{
		for (size_t j = 0; j < numberOfEachVegetation; j++)
		{
			FHitResult hit;
			FVector start = terrainLocation + FVector(UKismetMathLibrary::RandomFloatInRange(0, height * gridSize), UKismetMathLibrary::RandomFloatInRange(0, width * gridSize), 1000);
			FVector end = start - FVector(0, 0, 2500);
			world->LineTraceSingleByChannel(hit, start, end, ECC_Visibility);
			while ((hit.Actor != nullptr && hit.ImpactPoint.Z >= terrainLocation.Z && Cast<AProceduralTerrain>(hit.Actor)) == false)
			{
				start = terrainLocation + FVector(UKismetMathLibrary::RandomFloatInRange(0, height * gridSize), UKismetMathLibrary::RandomFloatInRange(0, width * gridSize), 1000);
				end = start - FVector(0, 0, 2500);
				world->LineTraceSingleByChannel(hit, start, end, ECC_Visibility);
			}

			FRotator rotation(0, UKismetMathLibrary::RandomFloatInRange(0, 360), 0);
			world->SpawnActor<AActor>(vegetationToSpawn[i], hit.ImpactPoint, rotation);
		}
	}
}

void AProceduralTerrain::AlignNavMeshToTerrain()
{
	if (navMesh)
	{
		FVector newLocation = GetActorLocation() + FVector((height * gridSize) / 2.0f, (width*gridSize) / 2.0f, 0);
		FVector newSize = FVector(height * (gridSize / 100.0f) / 2.0f, width * (gridSize / 100.0f) / 2.0f, 30);
		navMesh->SetActorLocation(newLocation);
		navMesh->SetActorScale3D(newSize);

		//Refresh navMesh by adding this actor to it's data and then rebuilding navMesh
		FNavigationSystem::UpdateActorAndComponentData(*this);
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "RebuildNavigation");
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign navMeshBoundsVolume in editor!"))
	}
}

void AProceduralTerrain::GenerateVertices()
{
	vertices.Reserve(height * width);
	FVector2D offset = FVector2D(UKismetMathLibrary::RandomFloatInRange(-99999999.9f, 99999999.9f), UKismetMathLibrary::RandomFloatInRange(-99999999.9f, 99999999.9f));
	for (size_t x = 0, i = 0; x <= height; x++, i++)
	{
		for (size_t y = 0; y <= width; y++, i++)
		{
			float _x = x * gridSize;
			float _y = y * gridSize;
			float _z = (USimplexNoiseBPLibrary::SimplexNoise2D(_x + offset.X, _y + offset.Y, 1.0f/scale) + noiseOffset_01) * heightMultiplier;
			vertices.Add(FVector(_x, _y, _z));
		}
	}
}

//void AProceduralTerrain::CalculateNormals()
//{
//	normals.Empty();
//	normals.Init(FVector(0,0,0), vertices.Num());
//
//	for (size_t i = 0; i < triangles.Num(); i += 3)
//	{
//		// Get the face normal
//		auto vector1 = vertices[triangles[i + 1]] - vertices[triangles[i]];
//		auto vector2 = vertices[triangles[i + 2]] - vertices[triangles[i]];
//		auto faceNormal = -FVector::CrossProduct(vector1, vector2);
//		faceNormal.Normalize();
//
//		// Add the face normal to the 3 vertices normal touching this face
//		normals[triangles[i]] += faceNormal;
//		normals[triangles[i + 1]] += faceNormal;
//		normals[triangles[i + 2]] += faceNormal;
//	}
//
//	// Normalize vertices normal
//	for (size_t i = 0; i < normals.Num(); i++)
//		normals[i].Normalize();
//}

void AProceduralTerrain::FillMesh()
{
	triangles.Reserve(height * width * 6);
	for (size_t x = 0, vi = 0; x < height; x++, vi++)
	{
		for (size_t y = 0; y < width; y++, vi++)
		{
			triangles.Add(vi);
			triangles.Add(vi + 1);
			triangles.Add(vi + width + 1);

			triangles.Add(vi + 1);
			triangles.Add(vi + width + 2);
			triangles.Add(vi + width + 1);
		}
	}
}

//void AProceduralTerrain::AddTriangle(const FVector& location_0, const FVector& location_1, const FVector& location_2)
//{
//	vertices.Add(location_0);
//	vertices.Add(location_1);
//	vertices.Add(location_2);
//
//	int32 lastVert = vertices.Num() - 1;
//	triangles.Add(lastVert - 2);
//	triangles.Add(lastVert);
//	triangles.Add(lastVert - 1);
//
//	uvs.Add(FVector2D(0.0f, 0.0f));
//	uvs.Add(FVector2D(1.0f, 0.0f));
//	uvs.Add(FVector2D(0.0f, 1.0f));
//}

void AProceduralTerrain::ClearMeshData()
{
	vertices.Empty();
	triangles.Empty();
	uvs.Empty();
	normals.Empty();
	vertexColors.Empty();
	tangents.Empty();
}