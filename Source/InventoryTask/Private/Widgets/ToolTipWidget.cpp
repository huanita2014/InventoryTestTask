// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ToolTipWidget.h"
#include "Components/TextBlock.h"

void UToolTipWidget::SetupTooltip(FText ItemName, FText ItemDescription)
{
	ItemNameTextBlock->SetText(ItemName);
	ItemDescriptionTextBlock->SetText(ItemDescription);
}
