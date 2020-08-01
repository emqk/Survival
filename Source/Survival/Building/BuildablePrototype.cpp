// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildablePrototype.h"

ABuildablePrototype::ABuildablePrototype()
{
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(meshComp);

	myWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	myWidget->AttachToComponent(meshComp, FAttachmentTransformRules::KeepRelativeTransform);
}