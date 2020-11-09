// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ClosableWidget.h"
#include "Components/Button.h"
#include "MyPlayerController.h"


void UClosableWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CloseButton->OnClicked.AddUniqueDynamic(this, &UClosableWidget::CloseWidget);

	if (PC)
	{
		PC->SetInputMode(FInputModeGameAndUI().SetWidgetToFocus(TakeWidget()));
	}
}

void UClosableWidget::SetPlayerController(AMyPlayerController* InPlayerController)
{
	PC = InPlayerController;	
}


void UClosableWidget::CloseWidget()
{
	if (PC)
	{
		PC->RemoveWidget(this);
	}
}
