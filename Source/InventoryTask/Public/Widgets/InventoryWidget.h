// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.h"
#include "MyCharacter.h"
#include "ClosableWidget.h"
#include "InventoryWidget.generated.h"

class AMyPlayerController;

UCLASS()
class INVENTORYTASK_API UInventoryWidget : public UClosableWidget
{
	GENERATED_BODY()
	
	protected:

	void NativeConstruct() override;

	virtual bool NativeOnDrop
	(
		const FGeometry & InGeometry,
		const FDragDropEvent & InDragDropEvent,
		UDragDropOperation * InOperation
	) override;
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* InventoryBorder;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* InventoryWrapBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UItemWidget> ItemWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	AMyCharacter* Character;

	class UInventoryComponent* InventoryComp;

	public:

	UFUNCTION()
	void FillWrapBox();

	void RemoveChildFromWrapbox(UUserWidget* ChildToRemove);
};
