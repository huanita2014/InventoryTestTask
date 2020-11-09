// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ItemSlot.h"
#include "ItemStats.h"
#include "MyPickup.generated.h"


UCLASS()
class INVENTORYTASK_API AMyPickup : public AInteractable
{
	GENERATED_BODY()
	
public:

	AMyPickup();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Interact(AActor* InteractFrom) override;

	//Needs to call after spawn during gameplay
	void Initialization(FItemSlot SlotInfo);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
	FItemSlot PickupSlot;

	void SetupPickupMesh();
};
