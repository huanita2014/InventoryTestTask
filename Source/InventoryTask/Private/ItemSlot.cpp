// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"


FItemSlot::FItemSlot()
{
	Count = 1;
}

FItemSlot::FItemSlot(FDataTableRowHandle OtherItem, int32 OtherCount)
{
	Item = OtherItem;
	Count = OtherCount;
}
