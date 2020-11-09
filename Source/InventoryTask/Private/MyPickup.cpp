// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPickup.h"
#include "InventoryComponent.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"

AMyPickup::AMyPickup()
{
	MeshComp->SetSimulatePhysics(true);
}

void AMyPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetupPickupMesh();
}

void AMyPickup::Interact(AActor* InteractFrom)
{
	AMyCharacter* Character = Cast<AMyCharacter>(InteractFrom);
	AMyPlayerController* PC = Cast<AMyPlayerController>(Character->GetController());
	if (PC->GetInventoryComponent()->AddToInventory(PickupSlot))
	{
		Destroy();
	}
}

void AMyPickup::Initialization(FItemSlot SlotInfo)
{
	PickupSlot = SlotInfo;
	SetupPickupMesh();
}

void AMyPickup::SetupPickupMesh()
{
	//Retrieving from the data table mesh of the pickup 
	if (PickupSlot.Item.DataTable)
	{
		static const FString ContextStr("");
		FItemStats* ItemStat = PickupSlot.Item.DataTable->FindRow<FItemStats>(PickupSlot.Item.RowName, ContextStr);
		if (ItemStat)
		{
			MeshComp->SetStaticMesh(ItemStat->ItemMesh);
		}
	}
}
