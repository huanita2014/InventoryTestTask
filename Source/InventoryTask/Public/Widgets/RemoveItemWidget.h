// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClosableWidget.h"
#include "ItemSlot.h"
#include "RemoveItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYTASK_API URemoveItemWidget : public UClosableWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

	void SetupRemoveWidget(class UItemWidget* ParentWidget);

protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* DropButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* MinusButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlusButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCountTextBlock;

	UFUNCTION()
	void Confirm();

	UFUNCTION()
	void HandlePlusButton();

	UFUNCTION()
	void HandleMinusButton();

	void UpdateCountTextBlock(int32 NewCount);

	class UItemWidget* Parent;

private:

	int32 CurrentCount;

	FItemSlot SlotToRemove;
};
