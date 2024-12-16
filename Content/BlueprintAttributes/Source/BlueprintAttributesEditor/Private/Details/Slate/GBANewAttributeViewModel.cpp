// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBANewAttributeViewModel.h"

FGBANewAttributeViewModel::FGBANewAttributeViewModel()
	: bIsReplicated(true)
{
}

void FGBANewAttributeViewModel::Initialize()
{
}

FString FGBANewAttributeViewModel::ToString() const
{
	return FString::Printf(
		TEXT("VariableName: %s, Description: %s, bIsReplicated: %s, CustomizedBlueprint: %s, PinType: %s"),
		*GetVariableName(),
		*GetDescription(),
		GetbIsReplicated() ? TEXT("true") : TEXT("false"),
		*GetNameSafe(GetCustomizedBlueprint().Get()),
		*GetNameSafe(GetPinType().PinSubCategoryObject.Get())
	);
}
