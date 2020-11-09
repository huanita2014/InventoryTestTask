// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/RemoveItemWidget.h"
#include "Widgets/ItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Math/UnrealMathUtility.h"
#include "MyPlayerController.h"

void URemoveItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Binding functions to buttons click
	DropButton->OnClicked.AddUniqueDynamic(this, &URemoveItemWidget::Confirm);
	PlusButton->OnClicked.AddUniqueDynamic(this, &URemoveItemWidget::HandlePlusButton);
	MinusButton->OnClicked.AddUniqueDynamic(this, &URemoveItemWidget::HandleMinusButton);
}

void URemoveItemWidget::SetupRemoveWidget(UItemWidget* ParentWidget)
{
	Parent = ParentWidget;
	SlotToRemove = Parent->GetItemSlot();
	CurrentCount = SlotToRemove.Count;
	UpdateCountTextBlock(CurrentCount);
}

void URemoveItemWidget::HandlePlusButton()
{
	CurrentCount = FMath::Clamp(++CurrentCount, 1, SlotToRemove.Count);
	UpdateCountTextBlock(CurrentCount);
}

void URemoveItemWidget::HandleMinusButton()
{
	CurrentCount = FMath::Clamp(--CurrentCount, 1, SlotToRemove.Count);
	UpdateCountTextBlock(CurrentCount);
}

void URemoveItemWidget::Confirm()
{
	Parent->RemoveItem(CurrentCount);
}

void URemoveItemWidget::UpdateCountTextBlock(int32 NewCount)
{
	ItemCountTextBlock->SetText(FText::AsNumber(NewCount));
}

