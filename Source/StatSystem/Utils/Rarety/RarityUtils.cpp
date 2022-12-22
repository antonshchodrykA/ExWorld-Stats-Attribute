

#include "RarityUtils.h"


void URarityUtils::GetRarityGroupDataByGroupName(FString ItemGroupName, FExWItemGroupData& ItemGroupData, bool& Success)
{
	FExWItemGroupData Result = FExWItemGroupData();

	const UDataTable* ItemGroupsTable = LoadObject<UDataTable>(
		nullptr, *UDataTablesConst::ItemGroupsDataTable());

	TArray<FName> ItemGroupsTableNames = ItemGroupsTable->GetRowNames();

	TArray<FExWItemGroupData> Coincidences;

	for (int32 i = 0; i < ItemGroupsTableNames.Num(); i++)
	{
		const FExWItemGroupData* Item = ItemGroupsTable->FindRow<FExWItemGroupData>(ItemGroupsTableNames[i], "");

		if (Item->Name == ItemGroupName)
		{
			Coincidences.Add(*Item);
			Success = true;
		}
	}

	Result = Coincidences[FMath::RandRange(0, Coincidences.Num() - 1)];

	ItemGroupData = Result;
}
