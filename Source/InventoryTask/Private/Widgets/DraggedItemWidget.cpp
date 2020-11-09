// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DraggedItemWidget.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UDraggedItemWidget::SetImageFromTexture(UTexture2D* Texture, int32 Width, int32 Height)
{
	ItemImage->SetBrush(UWidgetBlueprintLibrary::MakeBrushFromTexture(Texture, Width, Height));
}
