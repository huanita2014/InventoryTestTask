// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

UCLASS()
class INVENTORYTASK_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	class UImage* CrosshairImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair textures")
	UTexture2D* DefaultCrosshairTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair textures")
	UTexture2D* ActionCrosshairTexture;

	void UpdateCrosshairImage();

public:

	UFUNCTION(BlueprintCallable, Category = "Crosshais")
	void SetCrosshairToDefault();

	UFUNCTION(BlueprintCallable, Category = "Crosshais")
	void SetCrosshairToAction();

private:
	UTexture2D* CurrentCrosshair;
};
