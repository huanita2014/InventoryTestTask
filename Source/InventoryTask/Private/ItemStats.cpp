// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStats.h"


FItemStats::FItemStats()
{
	ItemName = FText::FromString("Item name");
	ItemDescription = FText::FromString("Item description");
	bIsStackable = true;
}
