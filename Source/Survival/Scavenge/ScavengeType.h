// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScavengeType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ScavengeType : uint8
{
	None, Wood, Stone, Consumable, Whatever
};