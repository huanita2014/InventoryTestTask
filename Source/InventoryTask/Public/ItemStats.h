// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemStats.generated.h"

USTRUCT(BlueprintType)
struct FItemStats : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemStats();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* ItemThumb;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStackable;

};
