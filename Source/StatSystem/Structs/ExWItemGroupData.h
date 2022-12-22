#pragma once

#include "CoreMinimal.h"
#include "ExWIntegerRange.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StatSystem/Enums/ExWItemRarety.h"
#include "ExWItemGroupData.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FExWItemGroupData : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemGroup")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemGroup")
	TEnumAsByte<EExWItemRarety> Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemGroup")
	FExWIntegerRange StatsCountDropPossibilityRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemGroup")
	FExWIntegerRange StatsCountDropValueRange;

};
