// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonStyleBase.h"


FPrimaryAssetId UButtonStyleBase::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("Styles"), GetFName());
}