// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "Components/WrapBox.h"
#include "Components/Border.h"
#include "Components/Button.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PC)
	{
		InventoryComp = PC->GetInventoryComponent();
		InventoryComp->OnItemAdded.AddUniqueDynamic(this, &UInventoryWidget::FillWrapBox);
		FillWrapBox();
	}
}

bool UInventoryWidget::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	// if dragged item drops to InventoryBorder just updating wrap box
	if (USlateBlueprintLibrary::IsUnderLocation(InventoryBorder->GetCachedGeometry(), InDragDropEvent.GetScreenSpacePosition()))
	{
		FillWrapBox();
		return true;
	}
	//if not removing appropriate slot from inventory
	UItemWidget* DroppedItem = Cast<UItemWidget>(InOperation->Payload);
	InventoryComp->RemoveSlotByIndex(DroppedItem->GetSlotIndex());
	FillWrapBox();
	return true;
}

void UInventoryWidget::FillWrapBox()
{
	InventoryWrapBox->ClearChildren();

	for (int32 SlotIndex = 0; SlotIndex < InventoryComp->GetInventory().Num(); SlotIndex++)
	{
		UItemWidget* CurrentItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidget);
		CurrentItemWidget->Initialization(this, SlotIndex);
		InventoryWrapBox->AddChild(CurrentItemWidget);
	}
}

void UInventoryWidget::RemoveChildFromWrapbox(UUserWidget* ChildToRemove)
{
	if (ChildToRemove && InventoryWrapBox->HasChild(ChildToRemove))
	{
		InventoryWrapBox->RemoveChild(ChildToRemove);
	}
}

