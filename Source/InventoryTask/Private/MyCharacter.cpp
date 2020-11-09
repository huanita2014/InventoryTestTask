// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "InventoryComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"
#include "Widgets/CrosshairWidget.h"
#include "MyPlayerController.h"
#include "MyPickup.h"
#include "Interactable.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	TraceLength = 300;

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AMyPlayerController* PC = Cast<AMyPlayerController>(GetController());
	InventoryComp = PC->GetInventoryComponent();
	InventoryComp->OnItemRemoved.AddDynamic(this, &AMyCharacter::CreateItem);

	CrossHairWidget = CreateWidget<UCrosshairWidget>(GetWorld(), CrosshairWidgetClass);
	if (CrossHairWidget)
	{
		CrossHairWidget->AddToViewport();
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForInteractables();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);
}

void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyCharacter::CheckForInteractables()
{
	FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndTrace = (FirstPersonCameraComponent->GetForwardVector() * TraceLength) + StartTrace;

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_WorldDynamic, CQP);
	if (HitResult.GetActor())
	{
		AInteractable* HitedInteractable = Cast<AInteractable>(HitResult.GetActor());
		if (HitedInteractable)
		{
			TracingInteractable = HitedInteractable;
			if (CrossHairWidget)
			{
				CrossHairWidget->SetCrosshairToAction();
			}
			return;
		}
	}
	TracingInteractable = nullptr;
	
	if (CrossHairWidget)
	{
		CrossHairWidget->SetCrosshairToDefault();
	}
}

void AMyCharacter::Interact()
{
	if (TracingInteractable)
	{
		TracingInteractable->Interact(this);
	}
}

void AMyCharacter::CreateItem(FItemSlot ItemToCreate)
{
	FVector SpawnLocation = ArrowComp->GetComponentLocation();
	FRotator SpawnRotation = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AMyPickup* PickupToCreate = GetWorld()->SpawnActor<AMyPickup>(SpawnLocation, SpawnRotation, SpawnParams);
	if (PickupToCreate)
	{
		PickupToCreate->Initialization(ItemToCreate);
	}	
}

