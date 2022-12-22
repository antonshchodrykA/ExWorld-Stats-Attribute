#include "EnumUtils.h"


int32 UEnumUtils::GetMaxEnumValue(FString EnumName)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *EnumName);

	const int32 CountOfEnum = EnumPtr->GetMaxEnumValue();

	return CountOfEnum;
}


