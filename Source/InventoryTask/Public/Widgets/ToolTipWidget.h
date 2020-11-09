// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolTipWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYTASK_API UToolTipWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetupTooltip(FText ItemName, FText ItemDescription);

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemDescriptionTextBlock;
};
