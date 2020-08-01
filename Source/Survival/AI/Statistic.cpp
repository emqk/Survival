// Fill out your copyright notice in the Description page of Project Settings.


#include "Statistic.h"

UStatistic::UStatistic()
{
}

UStatistic::~UStatistic()
{
}

void UStatistic::ChangeByAmount(const int& _amount)
{
	amount = FMath::Clamp(amount + _amount, minAmount, maxAmount);
}

int UStatistic::GetAmount() const
{
	return amount;
}