#pragma once

#include "CoreMinimal.h"

/**
 *
 */
UENUM(Blueprintable, BlueprintType)
enum class EExWAttributeType : uint8
{
	Health = 0,
	Mana = 1,
	Stamina = 2,
	Rage = 3,
	Damage = 4,
	MagicDamage = 5,
	Defense = 6,
	MagicDefense = 7,
	AttackSpeed = 8,
	Aim = 9,
	Evasion = 10,
	CriticalHitRate = 11,
	CriticalDamage = 12,
	CriticalNullifier = 13,
	CriticalDamageNullifier = 14,
	ArmorPenetration = 15,
	MagicArmorPenetration = 16,
	MovementSpeed = 17,
	CastSpeed = 18
};