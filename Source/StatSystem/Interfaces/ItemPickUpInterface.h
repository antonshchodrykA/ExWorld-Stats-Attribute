// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemPickUpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UItemPickUpInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class STATSYSTEM_API IItemPickUpInterface
{
	GENERATED_IINTERFACE_BODY()

public:

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PickUpItem(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DropItem(AActor* Item);

};
