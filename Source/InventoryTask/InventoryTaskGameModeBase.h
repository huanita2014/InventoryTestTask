// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "InventoryTaskGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYTASK_API AInventoryTaskGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AInventoryTaskGameModeBase();

	UDataTable* GetItemDataTable() { return this->ItemDataTable; } 

private:
	UDataTable* ItemDataTable;
};
