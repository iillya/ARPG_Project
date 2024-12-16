// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Utils/GBABlueprintLibrary.h"

#include "Abilities/GBAAttributeSetBlueprintBase.h"

FString UGBABlueprintLibrary::GetDebugStringFromExecutionData(const FGBAAttributeSetExecutionData& ExecutionData)
{
	return ExecutionData.ToString(LINE_TERMINATOR);
}

FString UGBABlueprintLibrary::GetDebugStringFromExecutionDataSeparator(const FGBAAttributeSetExecutionData& ExecutionData, const FString& Separator)
{
	return ExecutionData.ToString(Separator);
}

FString UGBABlueprintLibrary::GetDebugStringFromAttribute(const FGameplayAttribute& Attribute)
{
	return Attribute.GetName();
}

bool UGBABlueprintLibrary::NotEqual_GameplayAttributeGameplayAttribute(const FGameplayAttribute A, const FString B)
{
	return A.GetName() != B;
}

FText UGBABlueprintLibrary::GetAttributeDisplayNameText(const FGameplayAttribute& InAttribute)
{
	return FText::FromString(InAttribute.GetName());
}
