// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemWidget.h"
#include "MyGameStateBase.h"
#include "InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "InputCoreTypes.h"
#include "Widgets/InventoryWidget.h"
#include "Widgets/DraggedItemWidget.h"
#include "Widgets/ToolTipWidget.h"
#include "Widgets/RemoveItemWidget.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RemoveButton->OnClicked.AddUniqueDynamic(this, &UItemWidget::OpenRemovingWidget);
}

void UItemWidget::Initialization(UInventoryWidget* Parent, int32 SIndex)
{
	ParentWidget = Parent;
	SlotIndex = SIndex;
	PC = ParentWidget->GetPC();
	InventoryComp = PC->GetInventoryComponent();
	ItemSlot = InventoryComp->GetInventory()[SIndex];;

	//Searching for item data
	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	ItemStats = GS->FindItemByRowName(ItemSlot.Item.RowName);

	if (ItemStats)
	{
		//initializing components
		ItemImage->SetBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(
			ItemStats->ItemThumb, 
			DefaultThumbWidth, 
			DefaultThumbHeight));

		FText CountText = ItemStats->bIsStackable ? FText::AsNumber(ItemSlot.Count) : FText::FromString("");
		CountTextBlock->SetText(CountText);
	}

	//Tooltip initialization
	UToolTipWidget* TipWidget = Cast<UToolTipWidget>(CreateWidget(GetWorld(), ToolTipWidgetClass));
	TipWidget->SetupTooltip(ItemStats->ItemName, ItemStats->ItemDescription);
	SetToolTip(TipWidget);

	RemovingWidget = nullptr;
}


FReply UItemWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) 
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	return Reply;
}

void UItemWidget::NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent, UDragDropOperation *& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//hiding the widget when drag detected
	SetVisibility(ESlateVisibility::Hidden);

	UDraggedItemWidget* DraggedWidget = CreateWidget<UDraggedItemWidget>(GetWorld(), DraggedWidgetClass);
	DraggedWidget->SetImageFromTexture(ItemStats->ItemThumb, DefaultThumbWidth, DefaultThumbHeight);

	UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();
	DragOperation->DefaultDragVisual = DraggedWidget;
	DragOperation->Payload = this;
	OutOperation = DragOperation;
}

bool UItemWidget::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	UItemWidget* DroppedObject = Cast<UItemWidget>(InOperation->Payload);
	if (DroppedObject)
	{
		//Swapping items in inventory
		InventoryComp->SwapItems(DroppedObject->SlotIndex, SlotIndex);
		ParentWidget->FillWrapBox();
	}	
	return true;
}

void UItemWidget::OpenRemovingWidget()
{
	//if item is not stackable, just removing slot
	if (!ItemStats->bIsStackable || ItemSlot.Count == 1)
	{
		InventoryComp->RemoveSlotByIndex(SlotIndex);
		ParentWidget->FillWrapBox();
		return;
	}

	if (!RemovingWidget)
	{
		//Removing widget initialization
		RemovingWidget = CreateWidget<URemoveItemWidget>(GetWorld(), RemvoeWidgetClass);
		RemovingWidget->SetupRemoveWidget(this);
		RemovingWidget->SetPlayerController(PC);
	}

	if (!RemovingWidget->IsInViewport())
	{
		PC->AddWidgetToViewport(RemovingWidget);
	}
}

void UItemWidget::RemoveItem(int32 Count)
{
	InventoryComp->RemoveItemsBySlotIndex(SlotIndex, Count);
	if (RemovingWidget->IsInViewport())
	{
		RemovingWidget->CloseWidget();
	}
	ParentWidget->FillWrapBox();
}

