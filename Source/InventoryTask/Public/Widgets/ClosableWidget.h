// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClosableWidget.generated.h"

class AMyPlayerController;

UCLASS()
class INVENTORYTASK_API UClosableWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	AMyPlayerController* PC;

public:

	UFUNCTION()
	void CloseWidget();

	void SetPlayerController(AMyPlayerController* InPlayerController);

	AMyPlayerController* GetPC() { return PC; }
};
