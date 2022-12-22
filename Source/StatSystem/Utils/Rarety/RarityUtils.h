// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "StatSystem/Enums/ExWItemRarety.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "../../Structs/ExWItemGroupData.h"
#include "StatSystem/Consts/DataTablesConst.h"
#include "RarityUtils.generated.h"

/**
 *
 */
UCLASS()
class URarityUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static void GetRarityGroupDataByGroupName(FString ItemGroupName, FExWItemGroupData& ItemGroupData, bool& Success);
		
};
