#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ExWStatsData.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FExWStatsData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Agility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Endurance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Dexterity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Intelligence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Stamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Luck;
	
};
