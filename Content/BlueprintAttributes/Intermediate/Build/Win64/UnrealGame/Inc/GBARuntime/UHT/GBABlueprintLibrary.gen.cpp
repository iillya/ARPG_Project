// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributes/Public/Utils/GBABlueprintLibrary.h"
#include "BlueprintAttributes/Public/Abilities/GBAAttributeSetBlueprintBase.h"
#include "GameplayAbilities/Public/AttributeSet.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBABlueprintLibrary() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBABlueprintLibrary();
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBABlueprintLibrary_NoRegister();
BLUEPRINTATTRIBUTES_API UScriptStruct* Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttribute();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributes();
// End Cross Module References

// Begin Class UGBABlueprintLibrary Function GetAttributeDisplayNameText
struct Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics
{
	struct GBABlueprintLibrary_eventGetAttributeDisplayNameText_Parms
	{
		FGameplayAttribute InAttribute;
		FText ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** Returns the Attribute name as an FText */" },
		{ "ModuleRelativePath", "Public/Utils/GBABlueprintLibrary.h" },
		{ "ToolTip", "Returns the Attribute name as an FText" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FTextPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetAttributeDisplayNameText_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 2792951819
const UECodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetAttributeDisplayNameText_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::NewProp_InAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBABlueprintLibrary, nullptr, "GetAttributeDisplayNameText", nullptr, nullptr, Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::GBABlueprintLibrary_eventGetAttributeDisplayNameText_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::GBABlueprintLibrary_eventGetAttributeDisplayNameText_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBABlueprintLibrary::execGetAttributeDisplayNameText)
{
	P_GET_STRUCT_REF(FGameplayAttribute,Z_Param_Out_InAttribute);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FText*)Z_Param__Result=UGBABlueprintLibrary::GetAttributeDisplayNameText(Z_Param_Out_InAttribute);
	P_NATIVE_END;
}
// End Class UGBABlueprintLibrary Function GetAttributeDisplayNameText

// Begin Class UGBABlueprintLibrary Function GetDebugStringFromAttribute
struct Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics
{
	struct GBABlueprintLibrary_eventGetDebugStringFromAttribute_Parms
	{
		FGameplayAttribute Attribute;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** Returns the Attribute name */" },
		{ "ModuleRelativePath", "Public/Utils/GBABlueprintLibrary.h" },
		{ "ToolTip", "Returns the Attribute name" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attribute;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetDebugStringFromAttribute_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attribute_MetaData), NewProp_Attribute_MetaData) }; // 2792951819
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetDebugStringFromAttribute_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::NewProp_Attribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBABlueprintLibrary, nullptr, "GetDebugStringFromAttribute", nullptr, nullptr, Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::GBABlueprintLibrary_eventGetDebugStringFromAttribute_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::GBABlueprintLibrary_eventGetDebugStringFromAttribute_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBABlueprintLibrary::execGetDebugStringFromAttribute)
{
	P_GET_STRUCT_REF(FGameplayAttribute,Z_Param_Out_Attribute);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UGBABlueprintLibrary::GetDebugStringFromAttribute(Z_Param_Out_Attribute);
	P_NATIVE_END;
}
// End Class UGBABlueprintLibrary Function GetDebugStringFromAttribute

// Begin Class UGBABlueprintLibrary Function GetDebugStringFromExecutionData
struct Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics
{
	struct GBABlueprintLibrary_eventGetDebugStringFromExecutionData_Parms
	{
		FGBAAttributeSetExecutionData ExecutionData;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * Returns an FString representation of a FGBAAttributeSetExecutionData structure for debugging purposes.\n\x09 *\n\x09 * The separator used to join the data structure values is a line break (new line).\n\x09 *\n\x09 * @param ExecutionData\x09The data to get the debug string from.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Utils/GBABlueprintLibrary.h" },
		{ "ToolTip", "Returns an FString representation of a FGBAAttributeSetExecutionData structure for debugging purposes.\n\nThe separator used to join the data structure values is a line break (new line).\n\n@param ExecutionData The data to get the debug string from." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExecutionData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ExecutionData;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::NewProp_ExecutionData = { "ExecutionData", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetDebugStringFromExecutionData_Parms, ExecutionData), Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExecutionData_MetaData), NewProp_ExecutionData_MetaData) }; // 754966430
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetDebugStringFromExecutionData_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::NewProp_ExecutionData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBABlueprintLibrary, nullptr, "GetDebugStringFromExecutionData", nullptr, nullptr, Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::GBABlueprintLibrary_eventGetDebugStringFromExecutionData_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::GBABlueprintLibrary_eventGetDebugStringFromExecutionData_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBABlueprintLibrary::execGetDebugStringFromExecutionData)
{
	P_GET_STRUCT_REF(FGBAAttributeSetExecutionData,Z_Param_Out_ExecutionData);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UGBABlueprintLibrary::GetDebugStringFromExecutionData(Z_Param_Out_ExecutionData);
	P_NATIVE_END;
}
// End Class UGBABlueprintLibrary Function GetDebugStringFromExecutionData

// Begin Class UGBABlueprintLibrary Function GetDebugStringFromExecutionDataSeparator
struct Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics
{
	struct GBABlueprintLibrary_eventGetDebugStringFromExecutionDataSeparator_Parms
	{
		FGBAAttributeSetExecutionData ExecutionData;
		FString Separator;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * Returns an FString representation of a FGBAAttributeSetExecutionData structure for debugging purposes.\n\x09 *\n\x09 * @param ExecutionData\x09The data to get the debug string from.\n\x09 * @param Separator String separator to use when joining the structure values (Default: \"\\n\" - new line)\n\x09 */" },
		{ "CPP_Default_Separator", ", " },
		{ "ModuleRelativePath", "Public/Utils/GBABlueprintLibrary.h" },
		{ "ToolTip", "Returns an FString representation of a FGBAAttributeSetExecutionData structure for debugging purposes.\n\n@param ExecutionData The data to get the debug string from.\n@param Separator String separator to use when joining the structure values (Default: \"\\n\" - new line)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExecutionData_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Separator_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ExecutionData;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Separator;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::NewProp_ExecutionData = { "ExecutionData", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetDebugStringFromExecutionDataSeparator_Parms, ExecutionData), Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExecutionData_MetaData), NewProp_ExecutionData_MetaData) }; // 754966430
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::NewProp_Separator = { "Separator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetDebugStringFromExecutionDataSeparator_Parms, Separator), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Separator_MetaData), NewProp_Separator_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventGetDebugStringFromExecutionDataSeparator_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::NewProp_ExecutionData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::NewProp_Separator,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBABlueprintLibrary, nullptr, "GetDebugStringFromExecutionDataSeparator", nullptr, nullptr, Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::GBABlueprintLibrary_eventGetDebugStringFromExecutionDataSeparator_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::GBABlueprintLibrary_eventGetDebugStringFromExecutionDataSeparator_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBABlueprintLibrary::execGetDebugStringFromExecutionDataSeparator)
{
	P_GET_STRUCT_REF(FGBAAttributeSetExecutionData,Z_Param_Out_ExecutionData);
	P_GET_PROPERTY(FStrProperty,Z_Param_Separator);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UGBABlueprintLibrary::GetDebugStringFromExecutionDataSeparator(Z_Param_Out_ExecutionData,Z_Param_Separator);
	P_NATIVE_END;
}
// End Class UGBABlueprintLibrary Function GetDebugStringFromExecutionDataSeparator

// Begin Class UGBABlueprintLibrary Function NotEqual_GameplayAttributeGameplayAttribute
struct Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics
{
	struct GBABlueprintLibrary_eventNotEqual_GameplayAttributeGameplayAttribute_Parms
	{
		FGameplayAttribute A;
		FString B;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Blueprint Attributes | PinOptions" },
		{ "Comment", "/** Simple equality operator for gameplay attributes and string (for K2 Switch Node) */" },
		{ "ModuleRelativePath", "Public/Utils/GBABlueprintLibrary.h" },
		{ "ToolTip", "Simple equality operator for gameplay attributes and string (for K2 Switch Node)" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_A;
	static const UECodeGen_Private::FStrPropertyParams NewProp_B;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventNotEqual_GameplayAttributeGameplayAttribute_Parms, A), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(0, nullptr) }; // 2792951819
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBABlueprintLibrary_eventNotEqual_GameplayAttributeGameplayAttribute_Parms, B), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GBABlueprintLibrary_eventNotEqual_GameplayAttributeGameplayAttribute_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GBABlueprintLibrary_eventNotEqual_GameplayAttributeGameplayAttribute_Parms), &Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::NewProp_A,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::NewProp_B,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBABlueprintLibrary, nullptr, "NotEqual_GameplayAttributeGameplayAttribute", nullptr, nullptr, Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::GBABlueprintLibrary_eventNotEqual_GameplayAttributeGameplayAttribute_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::GBABlueprintLibrary_eventNotEqual_GameplayAttributeGameplayAttribute_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBABlueprintLibrary::execNotEqual_GameplayAttributeGameplayAttribute)
{
	P_GET_STRUCT(FGameplayAttribute,Z_Param_A);
	P_GET_PROPERTY(FStrProperty,Z_Param_B);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGBABlueprintLibrary::NotEqual_GameplayAttributeGameplayAttribute(Z_Param_A,Z_Param_B);
	P_NATIVE_END;
}
// End Class UGBABlueprintLibrary Function NotEqual_GameplayAttributeGameplayAttribute

// Begin Class UGBABlueprintLibrary
void UGBABlueprintLibrary::StaticRegisterNativesUGBABlueprintLibrary()
{
	UClass* Class = UGBABlueprintLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetAttributeDisplayNameText", &UGBABlueprintLibrary::execGetAttributeDisplayNameText },
		{ "GetDebugStringFromAttribute", &UGBABlueprintLibrary::execGetDebugStringFromAttribute },
		{ "GetDebugStringFromExecutionData", &UGBABlueprintLibrary::execGetDebugStringFromExecutionData },
		{ "GetDebugStringFromExecutionDataSeparator", &UGBABlueprintLibrary::execGetDebugStringFromExecutionDataSeparator },
		{ "NotEqual_GameplayAttributeGameplayAttribute", &UGBABlueprintLibrary::execNotEqual_GameplayAttributeGameplayAttribute },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBABlueprintLibrary);
UClass* Z_Construct_UClass_UGBABlueprintLibrary_NoRegister()
{
	return UGBABlueprintLibrary::StaticClass();
}
struct Z_Construct_UClass_UGBABlueprintLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/** Blueprint library for blueprint attribute sets */" },
		{ "IncludePath", "Utils/GBABlueprintLibrary.h" },
		{ "ModuleRelativePath", "Public/Utils/GBABlueprintLibrary.h" },
		{ "ToolTip", "Blueprint library for blueprint attribute sets" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGBABlueprintLibrary_GetAttributeDisplayNameText, "GetAttributeDisplayNameText" }, // 3862711254
		{ &Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromAttribute, "GetDebugStringFromAttribute" }, // 1524359746
		{ &Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionData, "GetDebugStringFromExecutionData" }, // 3921473428
		{ &Z_Construct_UFunction_UGBABlueprintLibrary_GetDebugStringFromExecutionDataSeparator, "GetDebugStringFromExecutionDataSeparator" }, // 3810573650
		{ &Z_Construct_UFunction_UGBABlueprintLibrary_NotEqual_GameplayAttributeGameplayAttribute, "NotEqual_GameplayAttributeGameplayAttribute" }, // 947785926
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBABlueprintLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGBABlueprintLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBABlueprintLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBABlueprintLibrary_Statics::ClassParams = {
	&UGBABlueprintLibrary::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBABlueprintLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBABlueprintLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBABlueprintLibrary()
{
	if (!Z_Registration_Info_UClass_UGBABlueprintLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBABlueprintLibrary.OuterSingleton, Z_Construct_UClass_UGBABlueprintLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBABlueprintLibrary.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UClass* StaticClass<UGBABlueprintLibrary>()
{
	return UGBABlueprintLibrary::StaticClass();
}
UGBABlueprintLibrary::UGBABlueprintLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBABlueprintLibrary);
UGBABlueprintLibrary::~UGBABlueprintLibrary() {}
// End Class UGBABlueprintLibrary

// Begin Registration
struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBABlueprintLibrary_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBABlueprintLibrary, UGBABlueprintLibrary::StaticClass, TEXT("UGBABlueprintLibrary"), &Z_Registration_Info_UClass_UGBABlueprintLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBABlueprintLibrary), 3982701889U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBABlueprintLibrary_h_1771086997(TEXT("/Script/BlueprintAttributes"),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBABlueprintLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBABlueprintLibrary_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
