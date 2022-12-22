#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StatSystem/Enums/ExWAttributeType.h"
#include "StatSystem/Enums/ExWStatType.h"
#include "ExWAttribute.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FExWAttribute : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EExWAttributeType AttributeType = EExWAttributeType::Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentValue = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsCapped : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIsCapped"))
	float MaxValue = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bCanBeBelowZero : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bDefaultCurrentValueZero : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EExWStatType StatType = EExWStatType::Agility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StatModifier = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bApplyRegen : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bApplyRegen"))
	float RegenValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bApplyRegen"))
	float RegenTickingRate = 1;

	/** Timer handle to manage this resource regeneration ticking*/
	FTimerHandle RegenTimerHandle;

	FExWAttribute()
	{
		// Default construction here
		bIsCapped = false;
		bCanBeBelowZero = false;
		bDefaultCurrentValueZero = false;
		bApplyRegen = false;
	};

	FExWAttribute(const EExWAttributeType NewAttributeType)
	{
		bIsCapped = false;
		bCanBeBelowZero = false;
		bDefaultCurrentValueZero = false;
		bApplyRegen = false;
		AttributeType = NewAttributeType;
	};

	FExWAttribute(const EExWAttributeType NewAttributeType,
	              const bool bNewIsCapped,
	              const bool bNewCanBeBelowZero,
	              const EExWStatType bNewStatType,
	              const float bNewStatModifier,
	              const bool bNewApplyRegen = false,
	              const float bNewRegenValue = 0,
	              const float bNewRegenTickingRate = 1,
	              const bool bNewDefaultCurrentValueZero = false)
	{
		AttributeType = NewAttributeType;
		bIsCapped = bNewIsCapped;
		bCanBeBelowZero = bNewCanBeBelowZero;
		StatType = bNewStatType;
		StatModifier = bNewStatModifier;
		bApplyRegen = bNewApplyRegen;
		RegenValue = bNewRegenValue;
		RegenTickingRate = bNewRegenTickingRate;
		bDefaultCurrentValueZero = bNewDefaultCurrentValueZero;
	};

	void GainAttribute(const float Value)
	{
		const float ModifiedValue = Value * StatModifier;

		if (CurrentValue + ModifiedValue > MaxValue && bIsCapped)
		{
			CurrentValue = MaxValue;
		}
		else if (!bCanBeBelowZero)
		{
			CurrentValue = FMath::Max(0.0f, CurrentValue + ModifiedValue);
		}
		else
		{
			CurrentValue = CurrentValue + ModifiedValue;
		}

	
	};

	void LoseAttribute(const float Value)
	{
		const float ModifiedValue = Value * StatModifier;

		if (CurrentValue - ModifiedValue >= 0)
		{
			CurrentValue = CurrentValue - ModifiedValue;
		}
		else if (bCanBeBelowZero)
		{
			CurrentValue = CurrentValue - ModifiedValue;
		}
		else
		{
			CurrentValue = 0;
		}
	};

	FORCEINLINE bool operator==(const FExWAttribute& rhs) const
	{
		return (rhs.AttributeType == this->AttributeType);
	};
};
