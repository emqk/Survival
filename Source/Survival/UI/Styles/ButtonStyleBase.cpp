// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonStyleBase.h"
#include "Components/TextBlock.h"


FPrimaryAssetId UButtonStyleBase::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType("Styles"), GetFName());
}

void UButtonStyleBase::SetStyleToButton(UButton* button)
{
	button->SetStyle(buttonStyle);
	UWidget* child = button->GetChildAt(0);
	if (child)
	{
		UTextBlock* childText = Cast<UTextBlock>(child);
		if (childText)
		{
			childText->SetFont(buttonTextStyle.Font);
			childText->SetColorAndOpacity(buttonTextStyle.ColorAndOpacity);
		}
	}
}
