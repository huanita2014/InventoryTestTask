// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

AMyGameStateBase::AMyGameStateBase()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDataTable(TEXT("DataTable'/Game/Data/ItemsTable.ItemsTable'"));
	ItemDataTable = BP_ItemDataTable.Object;
}

FItemStats* AMyGameStateBase::FindItemByRowName(FName RowName)
{
	if (ItemDataTable)
	{
		static const FString ContextStr("");
		FItemStats* ItemStat = ItemDataTable->FindRow<FItemStats>(RowName, ContextStr);
		if (ItemStat)
		{
			return ItemStat;
		}
	}
	return nullptr;
}
