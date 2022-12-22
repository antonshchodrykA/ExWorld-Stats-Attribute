// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AStatSystemCharacter

ABaseCharacter::ABaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	CreateDefaultAttributes();
	CreateDefaultStats();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABaseCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABaseCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABaseCharacter::OnResetVR);
}


void ABaseCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABaseCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ABaseCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ABaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void ABaseCharacter::PickUpItem_Implementation(AActor* Item)
{
	ApplyItemDataAttributesToStats(Cast<AItemBase>(Item));
}

void ABaseCharacter::DropItem_Implementation(AActor* Item)
{
	SubtractItemDataAttributesToStats(Cast<AItemBase>(Item));
}

void ABaseCharacter::CreateDefaultAttributes()
{
	Attributes.AddUnique(
		FExWAttribute(EExWAttributeType::Health, true, false, EExWStatType::Endurance, 10.f, true, 1.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::Mana, true, false, EExWStatType::Intelligence, 10.f, true,
	                                   1.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::Stamina, true, false, EExWStatType::Endurance, 5.f, true, 2.f,
	                                   .5f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::Rage, true, false, EExWStatType::Strength, 2.f, true, -.5f,
	                                   .5f, true));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::Damage, false, false, EExWStatType::Strength, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::MagicDamage, false, false, EExWStatType::Intelligence, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::Defense, false, false, EExWStatType::Endurance, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::MagicDefense, false, false, EExWStatType::Intelligence, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::AttackSpeed, false, false, EExWStatType::Agility, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::Aim, false, false, EExWStatType::Agility, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::Evasion, false, false, EExWStatType::Agility, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::CriticalHitRate, false, false, EExWStatType::Luck, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::CriticalDamage, false, false, EExWStatType::Luck, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::CriticalNullifier, false, false, EExWStatType::Luck, 5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::CriticalDamageNullifier, false, false, EExWStatType::Luck,
	                                   5.f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::ArmorPenetration, false, false, EExWStatType::Strength, .5f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::MagicArmorPenetration, false, false,
	                                   EExWStatType::Intelligence, .5f));
	Attributes.AddUnique(FExWAttribute(EExWAttributeType::CastSpeed, true, false, EExWStatType::Intelligence, 1.f));
}

void ABaseCharacter::CreateDefaultStats()
{
	Stats.AddUnique(FExWStat(EExWStatType::Strength));
	Stats.AddUnique(FExWStat(EExWStatType::Agility));
	Stats.AddUnique(FExWStat(EExWStatType::Endurance));
	Stats.AddUnique(FExWStat(EExWStatType::Intelligence));
	Stats.AddUnique(FExWStat(EExWStatType::Luck));
}


void ABaseCharacter::ApplyItemDataAttributesToStats(AItemBase* ItemBase)
{
	for (int32 ItemStatIndex = 0; ItemStatIndex < ItemBase->ItemData.ItemStatList.Num(); ItemStatIndex++)
	{
		const EExWAttributeType AttributeType = ItemBase->ItemData.ItemStatList[ItemStatIndex];
		const float AttributeValue = ItemBase->ItemData.ItemStatAleatoryValueList[ItemStatIndex];


		for (int32 AttributeIndex = 0; AttributeIndex < Attributes.Num(); AttributeIndex++)
		{
			FExWAttribute* Attribute = &Attributes[AttributeIndex];

			if (Attribute->AttributeType == AttributeType)
			{
				Attribute->GainAttribute(AttributeValue);
			}

			for (int32 StatIndex = 0; StatIndex < Stats.Num(); StatIndex++)
			{
				FExWStat* Stat = &Stats[StatIndex];

				if (Stat->StatType == Attribute->StatType)
				{
					Stat->GainStat(AttributeValue);
				}
			}
		}
	}

	OnAttributesAndStatsChanged.Broadcast();
}


void ABaseCharacter::SubtractItemDataAttributesToStats(AItemBase* ItemBase)
{
	for (int32 ItemStatIndex = 0; ItemStatIndex < ItemBase->ItemData.ItemStatList.Num(); ItemStatIndex++)
	{
		const EExWAttributeType AttributeType = ItemBase->ItemData.ItemStatList[ItemStatIndex];
		const float AttributeValue = ItemBase->ItemData.ItemStatAleatoryValueList[ItemStatIndex];


		for (int32 AttributeIndex = 0; AttributeIndex < Attributes.Num(); AttributeIndex++)
		{
			FExWAttribute* Attribute = &Attributes[AttributeIndex];

			if (Attribute->AttributeType == AttributeType)
			{
				Attribute->LoseAttribute(AttributeValue);
			}

			for (int32 StatIndex = 0; StatIndex < Stats.Num(); StatIndex++)
			{
				FExWStat* Stat = &Stats[StatIndex];

				if (Stat->StatType == Attribute->StatType)
				{
					Stat->LoseStat(AttributeValue);
				}
			}
		}
	}

	OnAttributesAndStatsChanged.Broadcast();
}

TArray<FExWAttributeTypeEffectOnStatType> ABaseCharacter::GetAttributeEffectorList()
{
	TArray<FExWAttributeTypeEffectOnStatType> Result;

	const UDataTable* AttributeEffectorTable = LoadObject<UDataTable>(
		nullptr, *UDataTablesConst::AttributeTypeEffectOnStatTypeDataTable());

	TArray<FName> AttributeEffectorTableNames = AttributeEffectorTable->GetRowNames();

	for (int32 AttributeEffectorTableNameIndex = 0; AttributeEffectorTableNameIndex < AttributeEffectorTableNames.Num();
	     AttributeEffectorTableNameIndex++)
	{
		const FExWAttributeTypeEffectOnStatType* AttributeEffector = AttributeEffectorTable
			->FindRow<FExWAttributeTypeEffectOnStatType>(AttributeEffectorTableNames[AttributeEffectorTableNameIndex],
			                                             "");

		Result.Add(*AttributeEffector);
	}

	return Result;
}
