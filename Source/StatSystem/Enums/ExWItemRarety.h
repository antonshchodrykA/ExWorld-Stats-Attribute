#pragma once

#include "CoreMinimal.h"

/**
 *
 */
UENUM(Blueprintable, BlueprintType)
enum class EExWItemRarety : uint8
{
    IR_Common = 0 UMETA(DisplayName = "Common"),
    IR_Uncommon = 1 UMETA(DisplayName = "Uncommon"),
    IR_Rare = 2 UMETA(DisplayName = "Rare"),
    IR_Epic = 3 UMETA(DisplayName = "Epic"),
    IR_Legendary = 4 UMETA(DisplayName = "Legendary")
};
