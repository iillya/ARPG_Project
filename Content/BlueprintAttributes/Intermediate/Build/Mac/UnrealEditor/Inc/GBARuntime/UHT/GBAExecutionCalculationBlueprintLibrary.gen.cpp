// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributes/Public/Utils/GBAExecutionCalculationBlueprintLibrary.h"
#include "GameplayAbilities/Public/AttributeSet.h"
#include "GameplayAbilities/Public/GameplayEffect.h"
#include "GameplayAbilities/Public/GameplayEffectAttributeCaptureDefinition.h"
#include "GameplayAbilities/Public/GameplayEffectExecutionCalculation.h"
#include "GameplayAbilities/Public/GameplayEffectTypes.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBAExecutionCalculationBlueprintLibrary() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary();
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
GAMEPLAYABILITIES_API UEnum* Z_Construct_UEnum_GameplayAbilities_EGameplayModOp();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttribute();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayEffectAttributeCaptureDefinition();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayEffectContextHandle();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionOutput();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionParameters();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayEffectSpec();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTagContainer();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributes();
// End Cross Module References

// Begin Class UGBAExecutionCalculationBlueprintLibrary Function AddOutputModifier
struct Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics
{
	struct GBAExecutionCalculationBlueprintLibrary_eventAddOutputModifier_Parms
	{
		FGameplayEffectCustomExecutionOutput InExecutionOutput;
		FGameplayAttribute InAttribute;
		TEnumAsByte<EGameplayModOp::Type> InModOp;
		float InMagnitude;
		FGameplayEffectCustomExecutionOutput ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes | Exec Calc" },
		{ "ModuleRelativePath", "Public/Utils/GBAExecutionCalculationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InModOp_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InMagnitude_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InExecutionOutput;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FBytePropertyParams NewProp_InModOp;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InMagnitude;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_InExecutionOutput = { "InExecutionOutput", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAddOutputModifier_Parms, InExecutionOutput), Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionOutput, METADATA_PARAMS(0, nullptr) }; // 1070385492
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAddOutputModifier_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 2792951819
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_InModOp = { "InModOp", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAddOutputModifier_Parms, InModOp), Z_Construct_UEnum_GameplayAbilities_EGameplayModOp, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InModOp_MetaData), NewProp_InModOp_MetaData) }; // 644670066
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_InMagnitude = { "InMagnitude", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAddOutputModifier_Parms, InMagnitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InMagnitude_MetaData), NewProp_InMagnitude_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAddOutputModifier_Parms, ReturnValue), Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionOutput, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 1070385492
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_InExecutionOutput,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_InAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_InModOp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_InMagnitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary, nullptr, "AddOutputModifier", nullptr, nullptr, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::GBAExecutionCalculationBlueprintLibrary_eventAddOutputModifier_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::GBAExecutionCalculationBlueprintLibrary_eventAddOutputModifier_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAExecutionCalculationBlueprintLibrary::execAddOutputModifier)
{
	P_GET_STRUCT_REF(FGameplayEffectCustomExecutionOutput,Z_Param_Out_InExecutionOutput);
	P_GET_STRUCT(FGameplayAttribute,Z_Param_InAttribute);
	P_GET_PROPERTY(FByteProperty,Z_Param_InModOp);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InMagnitude);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGameplayEffectCustomExecutionOutput*)Z_Param__Result=UGBAExecutionCalculationBlueprintLibrary::AddOutputModifier(Z_Param_Out_InExecutionOutput,Z_Param_InAttribute,EGameplayModOp::Type(Z_Param_InModOp),Z_Param_InMagnitude);
	P_NATIVE_END;
}
// End Class UGBAExecutionCalculationBlueprintLibrary Function AddOutputModifier

// Begin Class UGBAExecutionCalculationBlueprintLibrary Function AttemptCalculateCapturedAttributeMagnitude
struct Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics
{
	struct GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms
	{
		FGameplayEffectCustomExecutionParameters InExecutionParams;
		TArray<FGameplayEffectAttributeCaptureDefinition> InRelevantAttributesToCapture;
		FGameplayAttribute InAttribute;
		float OutMagnitude;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes | Exec Calc" },
		{ "ModuleRelativePath", "Public/Utils/GBAExecutionCalculationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InExecutionParams_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InRelevantAttributesToCapture_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InExecutionParams;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InRelevantAttributesToCapture_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InRelevantAttributesToCapture;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OutMagnitude;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_InExecutionParams = { "InExecutionParams", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms, InExecutionParams), Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionParameters, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InExecutionParams_MetaData), NewProp_InExecutionParams_MetaData) }; // 2964209672
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_InRelevantAttributesToCapture_Inner = { "InRelevantAttributesToCapture", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGameplayEffectAttributeCaptureDefinition, METADATA_PARAMS(0, nullptr) }; // 4129537336
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_InRelevantAttributesToCapture = { "InRelevantAttributesToCapture", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms, InRelevantAttributesToCapture), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InRelevantAttributesToCapture_MetaData), NewProp_InRelevantAttributesToCapture_MetaData) }; // 4129537336
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 2792951819
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_OutMagnitude = { "OutMagnitude", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms, OutMagnitude), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms), &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_InExecutionParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_InRelevantAttributesToCapture_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_InRelevantAttributesToCapture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_InAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_OutMagnitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary, nullptr, "AttemptCalculateCapturedAttributeMagnitude", nullptr, nullptr, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitude_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAExecutionCalculationBlueprintLibrary::execAttemptCalculateCapturedAttributeMagnitude)
{
	P_GET_STRUCT_REF(FGameplayEffectCustomExecutionParameters,Z_Param_Out_InExecutionParams);
	P_GET_TARRAY_REF(FGameplayEffectAttributeCaptureDefinition,Z_Param_Out_InRelevantAttributesToCapture);
	P_GET_STRUCT(FGameplayAttribute,Z_Param_InAttribute);
	P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_OutMagnitude);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGBAExecutionCalculationBlueprintLibrary::AttemptCalculateCapturedAttributeMagnitude(Z_Param_Out_InExecutionParams,Z_Param_Out_InRelevantAttributesToCapture,Z_Param_InAttribute,Z_Param_Out_OutMagnitude);
	P_NATIVE_END;
}
// End Class UGBAExecutionCalculationBlueprintLibrary Function AttemptCalculateCapturedAttributeMagnitude

// Begin Class UGBAExecutionCalculationBlueprintLibrary Function AttemptCalculateCapturedAttributeMagnitudeWithBase
struct Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics
{
	struct GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms
	{
		FGameplayEffectCustomExecutionParameters InExecutionParams;
		TArray<FGameplayEffectAttributeCaptureDefinition> InRelevantAttributesToCapture;
		FGameplayAttribute InAttribute;
		float InBaseValue;
		float OutMagnitude;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes | Exec Calc" },
		{ "ModuleRelativePath", "Public/Utils/GBAExecutionCalculationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InExecutionParams_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InRelevantAttributesToCapture_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InExecutionParams;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InRelevantAttributesToCapture_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InRelevantAttributesToCapture;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InBaseValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OutMagnitude;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InExecutionParams = { "InExecutionParams", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms, InExecutionParams), Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionParameters, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InExecutionParams_MetaData), NewProp_InExecutionParams_MetaData) }; // 2964209672
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InRelevantAttributesToCapture_Inner = { "InRelevantAttributesToCapture", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGameplayEffectAttributeCaptureDefinition, METADATA_PARAMS(0, nullptr) }; // 4129537336
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InRelevantAttributesToCapture = { "InRelevantAttributesToCapture", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms, InRelevantAttributesToCapture), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InRelevantAttributesToCapture_MetaData), NewProp_InRelevantAttributesToCapture_MetaData) }; // 4129537336
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 2792951819
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InBaseValue = { "InBaseValue", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms, InBaseValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InBaseValue_MetaData), NewProp_InBaseValue_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_OutMagnitude = { "OutMagnitude", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms, OutMagnitude), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms), &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InExecutionParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InRelevantAttributesToCapture_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InRelevantAttributesToCapture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_InBaseValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_OutMagnitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary, nullptr, "AttemptCalculateCapturedAttributeMagnitudeWithBase", nullptr, nullptr, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::GBAExecutionCalculationBlueprintLibrary_eventAttemptCalculateCapturedAttributeMagnitudeWithBase_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAExecutionCalculationBlueprintLibrary::execAttemptCalculateCapturedAttributeMagnitudeWithBase)
{
	P_GET_STRUCT_REF(FGameplayEffectCustomExecutionParameters,Z_Param_Out_InExecutionParams);
	P_GET_TARRAY_REF(FGameplayEffectAttributeCaptureDefinition,Z_Param_Out_InRelevantAttributesToCapture);
	P_GET_STRUCT(FGameplayAttribute,Z_Param_InAttribute);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InBaseValue);
	P_GET_PROPERTY_REF(FFloatProperty,Z_Param_Out_OutMagnitude);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UGBAExecutionCalculationBlueprintLibrary::AttemptCalculateCapturedAttributeMagnitudeWithBase(Z_Param_Out_InExecutionParams,Z_Param_Out_InRelevantAttributesToCapture,Z_Param_InAttribute,Z_Param_InBaseValue,Z_Param_Out_OutMagnitude);
	P_NATIVE_END;
}
// End Class UGBAExecutionCalculationBlueprintLibrary Function AttemptCalculateCapturedAttributeMagnitudeWithBase

// Begin Class UGBAExecutionCalculationBlueprintLibrary Function GetEffectContext
struct Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics
{
	struct GBAExecutionCalculationBlueprintLibrary_eventGetEffectContext_Parms
	{
		FGameplayEffectCustomExecutionParameters InExecutionParams;
		FGameplayEffectContextHandle ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes | Exec Calc" },
		{ "ModuleRelativePath", "Public/Utils/GBAExecutionCalculationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InExecutionParams_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InExecutionParams;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::NewProp_InExecutionParams = { "InExecutionParams", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventGetEffectContext_Parms, InExecutionParams), Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionParameters, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InExecutionParams_MetaData), NewProp_InExecutionParams_MetaData) }; // 2964209672
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventGetEffectContext_Parms, ReturnValue), Z_Construct_UScriptStruct_FGameplayEffectContextHandle, METADATA_PARAMS(0, nullptr) }; // 1628379207
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::NewProp_InExecutionParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary, nullptr, "GetEffectContext", nullptr, nullptr, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::GBAExecutionCalculationBlueprintLibrary_eventGetEffectContext_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::GBAExecutionCalculationBlueprintLibrary_eventGetEffectContext_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAExecutionCalculationBlueprintLibrary::execGetEffectContext)
{
	P_GET_STRUCT_REF(FGameplayEffectCustomExecutionParameters,Z_Param_Out_InExecutionParams);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGameplayEffectContextHandle*)Z_Param__Result=UGBAExecutionCalculationBlueprintLibrary::GetEffectContext(Z_Param_Out_InExecutionParams);
	P_NATIVE_END;
}
// End Class UGBAExecutionCalculationBlueprintLibrary Function GetEffectContext

// Begin Class UGBAExecutionCalculationBlueprintLibrary Function GetOwningSpec
struct Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics
{
	struct GBAExecutionCalculationBlueprintLibrary_eventGetOwningSpec_Parms
	{
		FGameplayEffectCustomExecutionParameters InExecutionParams;
		FGameplayEffectSpec ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes | Exec Calc" },
		{ "ModuleRelativePath", "Public/Utils/GBAExecutionCalculationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InExecutionParams_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InExecutionParams;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::NewProp_InExecutionParams = { "InExecutionParams", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventGetOwningSpec_Parms, InExecutionParams), Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionParameters, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InExecutionParams_MetaData), NewProp_InExecutionParams_MetaData) }; // 2964209672
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventGetOwningSpec_Parms, ReturnValue), Z_Construct_UScriptStruct_FGameplayEffectSpec, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 1577102320
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::NewProp_InExecutionParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary, nullptr, "GetOwningSpec", nullptr, nullptr, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::GBAExecutionCalculationBlueprintLibrary_eventGetOwningSpec_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::GBAExecutionCalculationBlueprintLibrary_eventGetOwningSpec_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAExecutionCalculationBlueprintLibrary::execGetOwningSpec)
{
	P_GET_STRUCT_REF(FGameplayEffectCustomExecutionParameters,Z_Param_Out_InExecutionParams);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGameplayEffectSpec*)Z_Param__Result=UGBAExecutionCalculationBlueprintLibrary::GetOwningSpec(Z_Param_Out_InExecutionParams);
	P_NATIVE_END;
}
// End Class UGBAExecutionCalculationBlueprintLibrary Function GetOwningSpec

// Begin Class UGBAExecutionCalculationBlueprintLibrary Function GetSourceTags
struct Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics
{
	struct GBAExecutionCalculationBlueprintLibrary_eventGetSourceTags_Parms
	{
		FGameplayEffectCustomExecutionParameters InExecutionParams;
		FGameplayTagContainer ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes | Exec Calc" },
		{ "ModuleRelativePath", "Public/Utils/GBAExecutionCalculationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InExecutionParams_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InExecutionParams;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::NewProp_InExecutionParams = { "InExecutionParams", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventGetSourceTags_Parms, InExecutionParams), Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionParameters, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InExecutionParams_MetaData), NewProp_InExecutionParams_MetaData) }; // 2964209672
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventGetSourceTags_Parms, ReturnValue), Z_Construct_UScriptStruct_FGameplayTagContainer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 3352185621
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::NewProp_InExecutionParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary, nullptr, "GetSourceTags", nullptr, nullptr, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::GBAExecutionCalculationBlueprintLibrary_eventGetSourceTags_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::GBAExecutionCalculationBlueprintLibrary_eventGetSourceTags_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAExecutionCalculationBlueprintLibrary::execGetSourceTags)
{
	P_GET_STRUCT_REF(FGameplayEffectCustomExecutionParameters,Z_Param_Out_InExecutionParams);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGameplayTagContainer*)Z_Param__Result=UGBAExecutionCalculationBlueprintLibrary::GetSourceTags(Z_Param_Out_InExecutionParams);
	P_NATIVE_END;
}
// End Class UGBAExecutionCalculationBlueprintLibrary Function GetSourceTags

// Begin Class UGBAExecutionCalculationBlueprintLibrary Function GetTargetTags
struct Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics
{
	struct GBAExecutionCalculationBlueprintLibrary_eventGetTargetTags_Parms
	{
		FGameplayEffectCustomExecutionParameters InExecutionParams;
		FGameplayTagContainer ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes | Exec Calc" },
		{ "ModuleRelativePath", "Public/Utils/GBAExecutionCalculationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InExecutionParams_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InExecutionParams;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::NewProp_InExecutionParams = { "InExecutionParams", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventGetTargetTags_Parms, InExecutionParams), Z_Construct_UScriptStruct_FGameplayEffectCustomExecutionParameters, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InExecutionParams_MetaData), NewProp_InExecutionParams_MetaData) }; // 2964209672
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAExecutionCalculationBlueprintLibrary_eventGetTargetTags_Parms, ReturnValue), Z_Construct_UScriptStruct_FGameplayTagContainer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 3352185621
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::NewProp_InExecutionParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary, nullptr, "GetTargetTags", nullptr, nullptr, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::GBAExecutionCalculationBlueprintLibrary_eventGetTargetTags_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::GBAExecutionCalculationBlueprintLibrary_eventGetTargetTags_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAExecutionCalculationBlueprintLibrary::execGetTargetTags)
{
	P_GET_STRUCT_REF(FGameplayEffectCustomExecutionParameters,Z_Param_Out_InExecutionParams);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGameplayTagContainer*)Z_Param__Result=UGBAExecutionCalculationBlueprintLibrary::GetTargetTags(Z_Param_Out_InExecutionParams);
	P_NATIVE_END;
}
// End Class UGBAExecutionCalculationBlueprintLibrary Function GetTargetTags

// Begin Class UGBAExecutionCalculationBlueprintLibrary
void UGBAExecutionCalculationBlueprintLibrary::StaticRegisterNativesUGBAExecutionCalculationBlueprintLibrary()
{
	UClass* Class = UGBAExecutionCalculationBlueprintLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AddOutputModifier", &UGBAExecutionCalculationBlueprintLibrary::execAddOutputModifier },
		{ "AttemptCalculateCapturedAttributeMagnitude", &UGBAExecutionCalculationBlueprintLibrary::execAttemptCalculateCapturedAttributeMagnitude },
		{ "AttemptCalculateCapturedAttributeMagnitudeWithBase", &UGBAExecutionCalculationBlueprintLibrary::execAttemptCalculateCapturedAttributeMagnitudeWithBase },
		{ "GetEffectContext", &UGBAExecutionCalculationBlueprintLibrary::execGetEffectContext },
		{ "GetOwningSpec", &UGBAExecutionCalculationBlueprintLibrary::execGetOwningSpec },
		{ "GetSourceTags", &UGBAExecutionCalculationBlueprintLibrary::execGetSourceTags },
		{ "GetTargetTags", &UGBAExecutionCalculationBlueprintLibrary::execGetTargetTags },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBAExecutionCalculationBlueprintLibrary);
UClass* Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_NoRegister()
{
	return UGBAExecutionCalculationBlueprintLibrary::StaticClass();
}
struct Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Blueprint library for blueprint attribute sets.\n *\n * Includes Gameplay Effect Execution Calculation helpers for Blueprint implementation of Exec Calc classes.\n */" },
		{ "IncludePath", "Utils/GBAExecutionCalculationBlueprintLibrary.h" },
		{ "ModuleRelativePath", "Public/Utils/GBAExecutionCalculationBlueprintLibrary.h" },
		{ "ToolTip", "Blueprint library for blueprint attribute sets.\n\nIncludes Gameplay Effect Execution Calculation helpers for Blueprint implementation of Exec Calc classes." },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AddOutputModifier, "AddOutputModifier" }, // 3141518750
		{ &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitude, "AttemptCalculateCapturedAttributeMagnitude" }, // 3212351360
		{ &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_AttemptCalculateCapturedAttributeMagnitudeWithBase, "AttemptCalculateCapturedAttributeMagnitudeWithBase" }, // 4005691608
		{ &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetEffectContext, "GetEffectContext" }, // 2242379872
		{ &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetOwningSpec, "GetOwningSpec" }, // 886196220
		{ &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetSourceTags, "GetSourceTags" }, // 3355279690
		{ &Z_Construct_UFunction_UGBAExecutionCalculationBlueprintLibrary_GetTargetTags, "GetTargetTags" }, // 3280079548
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBAExecutionCalculationBlueprintLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_Statics::ClassParams = {
	&UGBAExecutionCalculationBlueprintLibrary::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary()
{
	if (!Z_Registration_Info_UClass_UGBAExecutionCalculationBlueprintLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBAExecutionCalculationBlueprintLibrary.OuterSingleton, Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBAExecutionCalculationBlueprintLibrary.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UClass* StaticClass<UGBAExecutionCalculationBlueprintLibrary>()
{
	return UGBAExecutionCalculationBlueprintLibrary::StaticClass();
}
UGBAExecutionCalculationBlueprintLibrary::UGBAExecutionCalculationBlueprintLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBAExecutionCalculationBlueprintLibrary);
UGBAExecutionCalculationBlueprintLibrary::~UGBAExecutionCalculationBlueprintLibrary() {}
// End Class UGBAExecutionCalculationBlueprintLibrary

// Begin Registration
struct Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary, UGBAExecutionCalculationBlueprintLibrary::StaticClass, TEXT("UGBAExecutionCalculationBlueprintLibrary"), &Z_Registration_Info_UClass_UGBAExecutionCalculationBlueprintLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBAExecutionCalculationBlueprintLibrary), 4180414345U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_222134009(TEXT("/Script/BlueprintAttributes"),
	Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
