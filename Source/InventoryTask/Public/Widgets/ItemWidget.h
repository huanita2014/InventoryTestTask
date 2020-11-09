// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.h"
#include "ItemStats.h"
#include "ItemWidget.generated.h"


class UInventoryWidget;
class AMyPlayerController;

UCLASS()
class INVENTORYTASK_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:

		void NativeConstruct() override;
		
		void Initialization(UInventoryWidget* Parent, int32 SIndex);
	
		FItemSlot GetItemSlot() { return ItemSlot; }

		void RemoveItem(int32 Count);

		AMyPlayerController* GetPC() { return PC; }

		int32 GetSlotIndex() { return SlotIndex; }

	protected:

		virtual FReply NativeOnPreviewMouseButtonDown
		(
			const FGeometry& InGeometry,
			const FPointerEvent& InMouseEvent
		) override;

		virtual void NativeOnDragDetected
		(
			const FGeometry & InGeometry,
			const FPointerEvent & InMouseEvent,
			UDragDropOperation *& OutOperation
		) override;

		virtual bool NativeOnDrop
		(
			const FGeometry & InGeometry,
			const FDragDropEvent & InDragDropEvent,
			UDragDropOperation * InOperation
		) override;

		// UI components		
		UPROPERTY(meta = (BindWidget))
		class UButton* RemoveButton;

		UPROPERTY(meta = (BindWidget))
		class UTextBlock* CountTextBlock;

		UPROPERTY(meta = (BindWidget))
		class UImage* ItemImage;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Additional widgets")
		TSubclassOf<class UDraggedItemWidget> DraggedWidgetClass;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Additional widgets")
		TSubclassOf<class UToolTipWidget> ToolTipWidgetClass;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Additional widgets")
		TSubclassOf<class URemoveItemWidget> RemvoeWidgetClass;

		UFUNCTION()
		void OpenRemovingWidget();

		// Default width and height for ItemThumb (need to specify these values in BP)
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item thums")
		int32 DefaultThumbWidth;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item thums")
		int32 DefaultThumbHeight;

		FItemSlot ItemSlot;

		FItemStats* ItemStats;

		class URemoveItemWidget* RemovingWidget;

		AMyPlayerController* PC;

	private:
		
		class UInventoryComponent* InventoryComp;

		UInventoryWidget* ParentWidget;

		// Index of item slot in inventory
		int32 SlotIndex;
};
