#pragma once

#include "CoreMinimal.h"

/**
 *
 */
UENUM(Blueprintable, BlueprintType)
enum class EExWStatType : uint8
{
	Strength = 0,
	Agility = 1,
	Endurance = 2,
	Intelligence = 3,
	Luck = 4,
	Stamina = 5,
};
