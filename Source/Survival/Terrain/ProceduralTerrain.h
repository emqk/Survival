// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "ProceduralTerrain.generated.h"

UCLASS()
class SURVIVAL_API AProceduralTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralTerrain();

	void Generate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
		TArray<FVector> vertices;
	UPROPERTY()
		TArray<FVector> normals;
	UPROPERTY()
		TArray<int32> triangles;
	UPROPERTY()
		TArray<FVector2D> uvs;
	UPROPERTY()
		TArray<FColor> vertexColors;
	UPROPERTY()
		TArray<FProcMeshTangent> tangents;

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* material;
	UPROPERTY(EditAnywhere)
	ANavMeshBoundsVolume* navMesh;

	UPROPERTY(EditAnywhere)
	int numberOfEachVegetation = 10;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> vegetationToSpawn;

	UPROPERTY(EditAnywhere)
	int numberOfGrass = 10;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> grassToSpawn;

	UPROPERTY(EditAnywhere)
	float gridSize = 100.0f;

	UPROPERTY(EditAnywhere)
	float noiseOffset_01 = 0;
	UPROPERTY(EditAnywhere)
	float heightMultiplier = 100;
	UPROPERTY(EditAnywhere)
	float scale = 100;
	UPROPERTY(EditAnywhere)
	int width = 1;
	UPROPERTY(EditAnywhere)
	int height = 1;

private:
	void GenerateVegetation();

	void AlignNavMeshToTerrain();

	void GenerateVertices();
	//void CalculateNormals();
	void FillMesh();
	//void AddTriangle(const FVector& location_0, const FVector& location_1, const FVector& location_2);
	void ClearMeshData();
};