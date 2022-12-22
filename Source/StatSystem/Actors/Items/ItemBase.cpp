#include "ItemBase.h"

#include "Net/UnrealNetwork.h"


#define stringify( name ) # name

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	SetupInitialAttributes();
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AItemBase, ItemData);
}

void AItemBase::PickUp(ACharacter* PlayerCharacter)
{
	if (PlayerCharacter->GetClass()->ImplementsInterface(UItemPickUpInterface::StaticClass()))
	{
		IItemPickUpInterface::Execute_PickUpItem(PlayerCharacter, this);
		// This is the Execute_* function. The asterisk means your function name. :)
	}

	AttachToActor(PlayerCharacter, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AItemBase::PickUpServer_Implementation(ACharacter* PlayerCharacter)
{
}

void AItemBase::PickUpNetMulticast_Implementation(ACharacter* PlayerCharacter)
{
}

void AItemBase::Drop(ACharacter* PlayerCharacter)
{
}

void AItemBase::DropServer_Implementation(ACharacter* PlayerCharacter)
{
}

void AItemBase::DropNetMulticast_Implementation(ACharacter* PlayerCharacter)
{
}


void AItemBase::SetupInitialAttributes()
{
	//if (!UKismetSystemLibrary::IsServer(this) || !UKismetSystemLibrary::IsDedicatedServer(this))
	//	return;

	FExWItemData* SelfItemData = &ItemData;

	FExWItemGroupData ItemGroupData;
	bool Success;

	URarityUtils::GetRarityGroupDataByGroupName(ItemData.ItemStatDropGroup, ItemGroupData, Success);

	if (Success)
	{
		const int32 RandomItemStatsCount = FMath::RandRange(ItemGroupData.StatsCountDropPossibilityRange.Min,
		                                                    ItemGroupData.StatsCountDropPossibilityRange.Max);

		SelfItemData->ItemStatRarity = ItemGroupData.Rarity;

		for (int32 i = 0; i < RandomItemStatsCount; i++)
		{
			int RandomEExGearAttributeTypeIndex = FMath::RandRange(
				0, UEnumUtils::GetMaxEnumValue(stringify(EExWAttributeType)));

			EExWAttributeType EExGearAttributeTypeRandom = static_cast<EExWAttributeType>(
				RandomEExGearAttributeTypeIndex);

			SelfItemData->ItemStatList.Add(EExGearAttributeTypeRandom);

			SelfItemData->ItemStatAleatoryValueList.Add(
				FMath::RandRange(ItemGroupData.StatsCountDropValueRange.Min,
				                 ItemGroupData.StatsCountDropValueRange.Max));
		}
	}
	else
	{
		//This group don't exist
		UE_LOG(LogTemp, Error, TEXT("Error on SetupInitialAttributes!"));
	}
}
