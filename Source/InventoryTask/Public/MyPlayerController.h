// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UUserWidget;
class UInventoryComponent;
class UInventoryWidget;

UCLASS()
class INVENTORYTASK_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	AMyPlayerController();

	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void AddWidgetToViewport(UUserWidget* WidgetToAdd);

	UInventoryComponent* GetInventoryComponent() { return InventoryComp; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveCurrentWidget();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveWidget(UUserWidget* WidgetToRemove);

	UFUNCTION(Exec, Category = "Cheats")
	void AddItemToInventory(FName ItemRowName);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UInventoryWidget* InventoryWidget;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenInventoryWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UInventoryComponent* InventoryComp;

	void OnLastWidgetClosed();

private:

	UUserWidget* CurrentWidget;

	TArray<UUserWidget*> WidgetsInViewport;
};
