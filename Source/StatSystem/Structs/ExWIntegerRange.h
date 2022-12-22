#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ExWIntegerRange.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FExWIntegerRange : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STAT")
	int32 Max;
};
