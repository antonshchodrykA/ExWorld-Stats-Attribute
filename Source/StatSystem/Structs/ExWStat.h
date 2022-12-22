#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StatSystem/Enums/ExWAttributeType.h"
#include "StatSystem/Enums/ExWStatType.h"
#include "ExWStat.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FExWStat : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EExWStatType StatType = EExWStatType::Agility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value = 0;

	FExWStat()
	{
	};

	FExWStat(const EExWStatType NewStatType)
	{
		StatType = NewStatType;
	};

	FExWStat(const EExWStatType NewStatType, const float NewValue)
	{
		StatType = NewStatType;
		Value = NewValue;
	};

	void GainStat(const float InValue)
	{
		Value += InValue;
	};

	void LoseStat(const float InValue)
	{
		if (Value - InValue > 0)
		{
			Value -= InValue;
		}
		else
		{
			Value = 0;
		}
	};

	FORCEINLINE bool operator==(const FExWStat& rhs) const
	{
		return (rhs.StatType == this->StatType);
	};
};
