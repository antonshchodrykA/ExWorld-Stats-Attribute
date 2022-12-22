#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DataTablesConst.generated.h"

/**
 * 
 */
UCLASS()
class STATSYSTEM_API UDataTablesConst : public UObject
{
	GENERATED_BODY()

public:

	static FString ItemGroupsDataTable()  
	{
		return "/Game/DataTables/DT_ItemGroups.DT_ItemGroups"; 
	}

	static FString AttributeTypeEffectOnStatTypeDataTable()  
	{
		return "/Game/DataTables/DT_AttributeTypeEffectOnStatType.DT_AttributeTypeEffectOnStatType"; 
	}
};
