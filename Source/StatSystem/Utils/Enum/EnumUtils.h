// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EnumUtils.generated.h"

/**
 *
 */
UCLASS()
class UEnumUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static int32 GetMaxEnumValue(FString EnumName);
};
