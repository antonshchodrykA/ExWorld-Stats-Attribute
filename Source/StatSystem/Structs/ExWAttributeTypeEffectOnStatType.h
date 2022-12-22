#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StatSystem/Enums/ExWAttributeType.h"
#include "StatSystem/Enums/ExWStatType.h"
#include "ExWAttributeTypeEffectOnStatType.generated.h"

/**
 *
 */
USTRUCT(Blueprintable, BlueprintType)
struct FExWAttributeTypeEffectOnStatType : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	EExWAttributeType Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EExWStatType Stat;
};
