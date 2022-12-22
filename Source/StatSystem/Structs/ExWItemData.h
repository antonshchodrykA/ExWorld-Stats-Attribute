#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "../Enums/ExWItemRarety.h"
#include "../Enums/ExWAttributeType.h"
#include "ExWItemData.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FExWItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemStatDropGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemData")
	TEnumAsByte<EExWItemRarety> ItemStatRarity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemData")
	TArray<EExWAttributeType> ItemStatList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemData")
	TArray<float> ItemStatAleatoryValueList;
};
