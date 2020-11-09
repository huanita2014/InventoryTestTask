// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyGameStateBase.h"
#include "InventoryComponent.h"
#include "Widgets/InventoryWidget.h"

AMyPlayerController::AMyPlayerController()
{
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));

	CurrentWidget = nullptr;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Setup inventory widget
	InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	InventoryWidget->SetPlayerController(this);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMyPlayerController::OpenInventoryWidget);
	InputComponent->BindAction("Back", IE_Pressed, this, &AMyPlayerController::RemoveCurrentWidget);
}

void AMyPlayerController::AddWidgetToViewport(UUserWidget* WidgetToAdd)
{
	if (WidgetToAdd)
	{
		if (WidgetsInViewport.Num() == 0)
		{
			bShowMouseCursor = true;
			bEnableClickEvents = true;
		}
		WidgetToAdd->AddToViewport();
		WidgetsInViewport.Add(WidgetToAdd);
		CurrentWidget = WidgetToAdd;
	}
}

void AMyPlayerController::RemoveCurrentWidget()
{
	if (CurrentWidget && WidgetsInViewport.Contains(CurrentWidget))
	{
		WidgetsInViewport.Remove(CurrentWidget);
		CurrentWidget->RemoveFromParent();

		if (WidgetsInViewport.Num() > 0)
		{
			CurrentWidget = WidgetsInViewport.Last();
			return;
		}
		OnLastWidgetClosed();
	}
}

void AMyPlayerController::RemoveWidget(UUserWidget* WidgetToRemove)
{
	if (WidgetToRemove && WidgetsInViewport.Contains(WidgetToRemove))
	{
		if (WidgetToRemove == CurrentWidget)
		{
			RemoveCurrentWidget();
			return;
		}

		// if we have widgets which was added to viewport after the removing widget, remove them too
		int32 RemovingIndex = WidgetsInViewport.Find(WidgetToRemove);
		for (int32 i = RemovingIndex; i < WidgetsInViewport.Num(); i++)
		{
			WidgetsInViewport[i]->RemoveFromParent();
		}
	}

	if (WidgetsInViewport.Num() > 0)
	{
		OnLastWidgetClosed();
	}
}

void AMyPlayerController::OnLastWidgetClosed()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	CurrentWidget = nullptr;
	SetInputMode(FInputModeGameOnly());
}

void AMyPlayerController::OpenInventoryWidget()
{
	if (InventoryWidget && !InventoryWidget->IsInViewport())
	{
		AddWidgetToViewport(InventoryWidget);
	}
}

//Console command
void AMyPlayerController::AddItemToInventory(FName ItemRowName)
{
	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	
	if (GS->FindItemByRowName(ItemRowName))
	{
		UDataTable* DataTable = GS->GetItemDataTable();
		FDataTableRowHandle ItemRow;
		ItemRow.DataTable = DataTable;
		ItemRow.RowName = ItemRowName;

		FItemSlot AddedSlot(ItemRow, 1);
		InventoryComp->AddToInventory(AddedSlot);

		return;
	}
}
