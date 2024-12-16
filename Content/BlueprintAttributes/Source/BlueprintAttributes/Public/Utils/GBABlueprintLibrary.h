// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GBABlueprintLibrary.generated.h"

struct FGBAAttributeSetExecutionData;
struct FGameplayAttribute;


/** Blueprint library for blueprint attribute sets */
UCLASS()
class BLUEPRINTATTRIBUTES_API UGBABlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Returns an FString representation of a FGBAAttributeSetExecutionData structure for debugging purposes.
	 *
	 * The separator used to join the data structure values is a line break (new line).
	 *
	 * @param ExecutionData	The data to get the debug string from.
	 */
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes")
	static FString GetDebugStringFromExecutionData(const FGBAAttributeSetExecutionData& ExecutionData);

	/**
	 * Returns an FString representation of a FGBAAttributeSetExecutionData structure for debugging purposes.
	 *
	 * @param ExecutionData	The data to get the debug string from.
	 * @param Separator String separator to use when joining the structure values (Default: "\n" - new line)
	 */
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes")
	static FString GetDebugStringFromExecutionDataSeparator(const FGBAAttributeSetExecutionData& ExecutionData, const FString& Separator = TEXT(", "));

	/** Returns the Attribute name */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Blueprint Attributes")
	static FString GetDebugStringFromAttribute(const FGameplayAttribute& Attribute);

	/** Simple equality operator for gameplay attributes and string (for K2 Switch Node) */
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes | PinOptions", meta = (BlueprintInternalUseOnly = "true"))
	static bool NotEqual_GameplayAttributeGameplayAttribute(FGameplayAttribute A, FString B);

	/** Returns the Attribute name as an FText */
	UFUNCTION(BlueprintPure, Category = "Blueprint Attributes")
	static FText GetAttributeDisplayNameText(const FGameplayAttribute& InAttribute);
};
