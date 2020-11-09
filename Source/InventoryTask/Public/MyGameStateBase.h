// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/DataTable.h"
#include "ItemStats.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYTASK_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMyGameStateBase();

	UDataTable* GetItemDataTable() const { return this->ItemDataTable; }

	FItemStats* FindItemByRowName(FName RowName);

protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* ItemDataTable;
};
