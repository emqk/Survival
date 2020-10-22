// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogData.h"

FPrimaryAssetId UDialogData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("DialogDatas"), GetFName());
}
