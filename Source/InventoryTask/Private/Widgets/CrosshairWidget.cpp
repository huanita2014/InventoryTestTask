// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CrosshairWidget.h"
#include "Components/Image.h"


void UCrosshairWidget::SetCrosshairToDefault()
{
	if (DefaultCrosshairTexture && CurrentCrosshair != DefaultCrosshairTexture)
	{
		CurrentCrosshair = DefaultCrosshairTexture;
		UpdateCrosshairImage();
	}
}

void UCrosshairWidget::SetCrosshairToAction()
{
	if (ActionCrosshairTexture && CurrentCrosshair != ActionCrosshairTexture)
	{
		CurrentCrosshair = ActionCrosshairTexture;
		UpdateCrosshairImage();
	}
}

void UCrosshairWidget::UpdateCrosshairImage()
{
	CrosshairImage->SetBrushFromTexture(CurrentCrosshair, true);
}
