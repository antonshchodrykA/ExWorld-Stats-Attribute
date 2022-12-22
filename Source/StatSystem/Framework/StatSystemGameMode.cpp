// Copyright Epic Games, Inc. All Rights Reserved.

#include "StatSystemGameMode.h"
#include "../Character/BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStatSystemGameMode::AStatSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
