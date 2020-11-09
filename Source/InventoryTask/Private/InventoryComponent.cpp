// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Engine/DataTable.h"
#include "MyGameStateBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	SlotLimit = 100;
}

bool UInventoryComponent::AddToInventory(FItemSlot ItemToAdd)
{
	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	FItemStats* ItemStats = GS->FindItemByRowName(ItemToAdd.Item.RowName);

	if (ItemStats->bIsStackable)
	{
		for (auto &ItemSlot : Inventory)
		{
			if (ItemSlot.Item == ItemToAdd.Item)
			{
				ItemSlot.Count += ItemToAdd.Count;
				OnItemAdded.Broadcast();
				return true;
			}
		}
	}
	
	if (Inventory.Num() < SlotLimit)
	{
		Inventory.Add(ItemToAdd);
		OnItemAdded.Broadcast();
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Not enough space in inventory"));
	return false;
}

void UInventoryComponent::RemoveItemsBySlotIndex(int32 SlotIndex, int32 Count)
{
	if (Inventory.IsValidIndex(SlotIndex))
	{
		Inventory[SlotIndex].Count -= Count;
		FItemSlot RemovedItem(Inventory[SlotIndex].Item, Count);
		OnItemRemoved.Broadcast(FItemSlot(RemovedItem));
		if (Inventory[SlotIndex].Count < 1)
		{
			Inventory.RemoveAt(SlotIndex);
		}
	}
}

void UInventoryComponent::RemoveSlotByIndex(int32 SlotIndex)
{
	if (Inventory.IsValidIndex(SlotIndex))
	{
		OnItemRemoved.Broadcast(Inventory[SlotIndex]);
		Inventory.RemoveAt(SlotIndex);
	}
}

void UInventoryComponent::SwapItems(int32 LeftIndex, int32 RightIndex)
{
	Inventory.Swap(LeftIndex, RightIndex);
}

