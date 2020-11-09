// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggedItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYTASK_API UDraggedItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:

		void SetImageFromTexture(UTexture2D* Texture, int32 Width, int32 Height);

	protected:

		UPROPERTY(meta = (BindWidget))
		class UImage* ItemImage;
};
