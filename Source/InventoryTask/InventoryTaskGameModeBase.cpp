// Copyright Epic Games, Inc. All Rights Reserved.


#include "InventoryTaskGameModeBase.h"

AInventoryTaskGameModeBase::AInventoryTaskGameModeBase()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDataTable(TEXT("DataTable'/Game/Data/ItemsTable.ItemsTable'"));
	ItemDataTable = BP_ItemDataTable.Object;
}
