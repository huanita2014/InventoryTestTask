// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemSlot.generated.h"

USTRUCT(BlueprintType)
struct FItemSlot
{
	GENERATED_BODY()

public:

	FItemSlot();

	FItemSlot(FDataTableRowHandle OtherItem, int32 OtherCount);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle Item;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Count;

	friend bool operator== (const FItemSlot& Left, const FItemSlot& Right)
	{
		if (Left.Item == Right.Item && Left.Count == Right.Count)
		{
			return true;
		}
		return false;
	}
};
