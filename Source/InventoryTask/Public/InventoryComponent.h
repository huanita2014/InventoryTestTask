// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemStats.h"
#include "ItemSlot.h"
#include "InventoryComponent.generated.h"


//On item removed from inventory delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemovedSignature, FItemSlot, RemovedItem);

//OnItem added to inventory delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAddedSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYTASK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:

	TArray<FItemSlot> Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 SlotLimit;
public:	

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<FItemSlot> GetInventory() { return this->Inventory; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddToInventory(FItemSlot ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemsBySlotIndex(int32 SlotIndex, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveSlotByIndex(int32 SlotIndex);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemRemovedSignature OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemAddedSignature OnItemAdded;
	
	void SwapItems(int32 LeftIndex, int32 RightIndex);
};
