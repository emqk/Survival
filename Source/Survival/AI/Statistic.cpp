// Fill out your copyright notice in the Description page of Project Settings.


#include "Statistic.h"

const float UStatistic::maxAmount = 100;
const float UStatistic::minAmount = 0;

UStatistic::UStatistic()
{
}

UStatistic::~UStatistic()
{
}

void UStatistic::ChangeByAmount(const float& _amount)
{
	amount = FMath::Clamp(amount + _amount, minAmount, maxAmount);
}

float UStatistic::GetAmountNormalized() const
{
	return GetAmount() / maxAmount;
}

float UStatistic::GetAmount() const
{
	return amount;
}