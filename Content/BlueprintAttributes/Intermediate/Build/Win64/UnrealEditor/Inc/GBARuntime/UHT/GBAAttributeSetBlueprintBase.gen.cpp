// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributes/Public/Abilities/GBAAttributeSetBlueprintBase.h"
#include "GameplayAbilities/Public/Abilities/GameplayAbilityTypes.h"
#include "GameplayAbilities/Public/AttributeSet.h"
#include "GameplayAbilities/Public/GameplayEffectTypes.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
#include "Serialization/ArchiveUObjectFromStructuredArchive.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBAAttributeSetBlueprintBase() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBAAttributeSetBlueprintBase();
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBAAttributeSetBlueprintBase_NoRegister();
BLUEPRINTATTRIBUTES_API UEnum* Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType();
BLUEPRINTATTRIBUTES_API UScriptStruct* Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData();
BLUEPRINTATTRIBUTES_API UScriptStruct* Z_Construct_UScriptStruct_FGBAClampDefinition();
BLUEPRINTATTRIBUTES_API UScriptStruct* Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerController_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemComponent_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAttributeSet();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAbilityActorInfo();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttribute();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttributeData();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayEffectContextHandle();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTagContainer();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributes();
// End Cross Module References

// Begin ScriptStruct FGBAAttributeSetExecutionData
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GBAAttributeSetExecutionData;
class UScriptStruct* FGBAAttributeSetExecutionData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GBAAttributeSetExecutionData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GBAAttributeSetExecutionData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData, (UObject*)Z_Construct_UPackage__Script_BlueprintAttributes(), TEXT("GBAAttributeSetExecutionData"));
	}
	return Z_Registration_Info_UScriptStruct_GBAAttributeSetExecutionData.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UScriptStruct* StaticStruct<FGBAAttributeSetExecutionData>()
{
	return FGBAAttributeSetExecutionData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Structure holding various information to deal with AttributeSet lifecycle events (such as Pre/PostGameplayEffectExecute),\n * extracting info from FGameplayEffectModCallbackData.\n */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Structure holding various information to deal with AttributeSet lifecycle events (such as Pre/PostGameplayEffectExecute),\nextracting info from FGameplayEffectModCallbackData." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceActor_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** The physical representation of the Source ASC (The ability system component of the instigator that started the whole chain) */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "The physical representation of the Source ASC (The ability system component of the instigator that started the whole chain)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetActor_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** The physical representation of the owner (Avatar) for the target we intend to apply to  */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "The physical representation of the owner (Avatar) for the target we intend to apply to" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceASC_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** The ability system component of the instigator that started the whole chain */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "The ability system component of the instigator that started the whole chain" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetASC_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** The ability system component we intend to apply to */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "The ability system component we intend to apply to" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceController_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** PlayerController associated with the owning actor for the Source ASC (The ability system component of the instigator that started the whole chain) */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "PlayerController associated with the owning actor for the Source ASC (The ability system component of the instigator that started the whole chain)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetController_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** PlayerController associated with the owning actor for the target we intend to apply to */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "PlayerController associated with the owning actor for the target we intend to apply to" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceObject_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** The object this effect was created from. */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "The object this effect was created from." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Context_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** This tells us how we got here (who / what applied us) */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "This tells us how we got here (who / what applied us)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceTags_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** Combination of spec and actor tags for the captured Source Tags on GameplayEffectSpec creation */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Combination of spec and actor tags for the captured Source Tags on GameplayEffectSpec creation" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpecAssetTags_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** All tags that apply to the gameplay effect spec */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "All tags that apply to the gameplay effect spec" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MagnitudeValue_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** Holds the modifier magnitude value, if it is available (for scalable floats) */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Holds the modifier magnitude value, if it is available (for scalable floats)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeltaValue_MetaData[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** Holds the delta value between old and new, if it is available (for Additive Operations) */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Holds the delta value between old and new, if it is available (for Additive Operations)" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SourceActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SourceASC;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetASC;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SourceController;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetController;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SourceObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Context;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SourceTags;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SpecAssetTags;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MagnitudeValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGBAAttributeSetExecutionData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceActor = { "SourceActor", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, SourceActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceActor_MetaData), NewProp_SourceActor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_TargetActor = { "TargetActor", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, TargetActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetActor_MetaData), NewProp_TargetActor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceASC = { "SourceASC", nullptr, (EPropertyFlags)0x011400000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, SourceASC), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceASC_MetaData), NewProp_SourceASC_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_TargetASC = { "TargetASC", nullptr, (EPropertyFlags)0x011400000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, TargetASC), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetASC_MetaData), NewProp_TargetASC_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceController = { "SourceController", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, SourceController), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceController_MetaData), NewProp_SourceController_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_TargetController = { "TargetController", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, TargetController), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetController_MetaData), NewProp_TargetController_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceObject = { "SourceObject", nullptr, (EPropertyFlags)0x0114000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, SourceObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceObject_MetaData), NewProp_SourceObject_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_Context = { "Context", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, Context), Z_Construct_UScriptStruct_FGameplayEffectContextHandle, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Context_MetaData), NewProp_Context_MetaData) }; // 1628379207
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceTags = { "SourceTags", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, SourceTags), Z_Construct_UScriptStruct_FGameplayTagContainer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceTags_MetaData), NewProp_SourceTags_MetaData) }; // 3352185621
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SpecAssetTags = { "SpecAssetTags", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, SpecAssetTags), Z_Construct_UScriptStruct_FGameplayTagContainer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpecAssetTags_MetaData), NewProp_SpecAssetTags_MetaData) }; // 3352185621
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_MagnitudeValue = { "MagnitudeValue", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, MagnitudeValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MagnitudeValue_MetaData), NewProp_MagnitudeValue_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_DeltaValue = { "DeltaValue", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAAttributeSetExecutionData, DeltaValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeltaValue_MetaData), NewProp_DeltaValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_TargetActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceASC,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_TargetASC,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceController,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_TargetController,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_Context,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SourceTags,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_SpecAssetTags,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_MagnitudeValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewProp_DeltaValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
	nullptr,
	&NewStructOps,
	"GBAAttributeSetExecutionData",
	Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::PropPointers),
	sizeof(FGBAAttributeSetExecutionData),
	alignof(FGBAAttributeSetExecutionData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000205),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData()
{
	if (!Z_Registration_Info_UScriptStruct_GBAAttributeSetExecutionData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GBAAttributeSetExecutionData.InnerSingleton, Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GBAAttributeSetExecutionData.InnerSingleton;
}
// End ScriptStruct FGBAAttributeSetExecutionData

// Begin Enum EGBAClampingType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGBAClampingType;
static UEnum* EGBAClampingType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EGBAClampingType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EGBAClampingType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType, (UObject*)Z_Construct_UPackage__Script_BlueprintAttributes(), TEXT("EGBAClampingType"));
	}
	return Z_Registration_Info_UEnum_EGBAClampingType.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UEnum* StaticEnum<EGBAClampingType>()
{
	return EGBAClampingType_StaticEnum();
}
struct Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "AttributeBased.Comment", "/** Perform a clamping based upon another attribute. */" },
		{ "AttributeBased.Name", "EGBAClampingType::AttributeBased" },
		{ "AttributeBased.ToolTip", "Perform a clamping based upon another attribute." },
		{ "Comment", "/** Enumeration outlining the possible gameplay effect magnitude calculation policies. */" },
		{ "Float.Comment", "/** Use a simple, static float for the clamping. */" },
		{ "Float.Name", "EGBAClampingType::Float" },
		{ "Float.ToolTip", "Use a simple, static float for the clamping." },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "None.Comment", "/** Clamping is disabled for this definition */" },
		{ "None.Name", "EGBAClampingType::None" },
		{ "None.ToolTip", "Clamping is disabled for this definition" },
		{ "ToolTip", "Enumeration outlining the possible gameplay effect magnitude calculation policies." },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGBAClampingType::None", (int64)EGBAClampingType::None },
		{ "EGBAClampingType::Float", (int64)EGBAClampingType::Float },
		{ "EGBAClampingType::AttributeBased", (int64)EGBAClampingType::AttributeBased },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_BlueprintAttributes,
	nullptr,
	"EGBAClampingType",
	"EGBAClampingType",
	Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType()
{
	if (!Z_Registration_Info_UEnum_EGBAClampingType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGBAClampingType.InnerSingleton, Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EGBAClampingType.InnerSingleton;
}
// End Enum EGBAClampingType

// Begin ScriptStruct FGBAClampDefinition
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GBAClampDefinition;
class UScriptStruct* FGBAClampDefinition::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GBAClampDefinition.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GBAClampDefinition.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGBAClampDefinition, (UObject*)Z_Construct_UPackage__Script_BlueprintAttributes(), TEXT("GBAClampDefinition"));
	}
	return Z_Registration_Info_UScriptStruct_GBAClampDefinition.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UScriptStruct* StaticStruct<FGBAClampDefinition>()
{
	return FGBAClampDefinition::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGBAClampDefinition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClampType_MetaData[] = {
		{ "Category", "Clamp" },
		{ "Comment", "/** Type of clamping to perform (either static float or attribute based) */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Type of clamping to perform (either static float or attribute based)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "Category", "Clamp" },
		{ "Comment", "/** Float value to base the clamping on */" },
		{ "EditCondition", "ClampType == EGBAClampingType::Float" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Float value to base the clamping on" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attribute_MetaData[] = {
		{ "Category", "Clamp" },
		{ "Comment", "/**\n\x09 * Gameplay Attribute to base the clamping on (for example, MaxHealth when clamping the Health attribute)\n\x09 *\n\x09 * Only \"owned\" attributes will be displayed here, meaning attributes that are part of the same Attribute Set class (eg. same owner)\n\x09 */" },
		{ "EditCondition", "ClampType == EGBAClampingType::AttributeBased" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ShowOnlyOwnedAttributes", "" },
		{ "ToolTip", "Gameplay Attribute to base the clamping on (for example, MaxHealth when clamping the Health attribute)\n\nOnly \"owned\" attributes will be displayed here, meaning attributes that are part of the same Attribute Set class (eg. same owner)" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_ClampType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ClampType;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attribute;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGBAClampDefinition>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewProp_ClampType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewProp_ClampType = { "ClampType", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAClampDefinition, ClampType), Z_Construct_UEnum_BlueprintAttributes_EGBAClampingType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClampType_MetaData), NewProp_ClampType_MetaData) }; // 3580240750
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAClampDefinition, Value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAClampDefinition, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attribute_MetaData), NewProp_Attribute_MetaData) }; // 2792951819
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewProp_ClampType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewProp_ClampType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewProp_Attribute,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
	nullptr,
	&NewStructOps,
	"GBAClampDefinition",
	Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::PropPointers),
	sizeof(FGBAClampDefinition),
	alignof(FGBAClampDefinition),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGBAClampDefinition()
{
	if (!Z_Registration_Info_UScriptStruct_GBAClampDefinition.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GBAClampDefinition.InnerSingleton, Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GBAClampDefinition.InnerSingleton;
}
// End ScriptStruct FGBAClampDefinition

// Begin ScriptStruct FGBAGameplayClampedAttributeData
static_assert(std::is_polymorphic<FGBAGameplayClampedAttributeData>() == std::is_polymorphic<FGameplayAttributeData>(), "USTRUCT FGBAGameplayClampedAttributeData cannot be polymorphic unless super FGameplayAttributeData is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GBAGameplayClampedAttributeData;
class UScriptStruct* FGBAGameplayClampedAttributeData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GBAGameplayClampedAttributeData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GBAGameplayClampedAttributeData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData, (UObject*)Z_Construct_UPackage__Script_BlueprintAttributes(), TEXT("GBAGameplayClampedAttributeData"));
	}
	return Z_Registration_Info_UScriptStruct_GBAGameplayClampedAttributeData.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UScriptStruct* StaticStruct<FGBAGameplayClampedAttributeData>()
{
	return FGBAGameplayClampedAttributeData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "/**\n * Place in a Blueprint AttributeSet to create an attribute that can be accessed using FGameplayAttribute.\n *\n * This one has clamping functionality built-in (compared to FGameplayAttributeData)\n */" },
		{ "DisplayName", "Gameplay Clamped Attribute Data" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Place in a Blueprint AttributeSet to create an attribute that can be accessed using FGameplayAttribute.\n\nThis one has clamping functionality built-in (compared to FGameplayAttributeData)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinValue_MetaData[] = {
		{ "Category", "Min" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxValue_MetaData[] = {
		{ "Category", "Max" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_MinValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MaxValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGBAGameplayClampedAttributeData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::NewProp_MinValue = { "MinValue", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAGameplayClampedAttributeData, MinValue), Z_Construct_UScriptStruct_FGBAClampDefinition, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinValue_MetaData), NewProp_MinValue_MetaData) }; // 2728223817
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::NewProp_MaxValue = { "MaxValue", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAGameplayClampedAttributeData, MaxValue), Z_Construct_UScriptStruct_FGBAClampDefinition, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxValue_MetaData), NewProp_MaxValue_MetaData) }; // 2728223817
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::NewProp_MinValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::NewProp_MaxValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
	Z_Construct_UScriptStruct_FGameplayAttributeData,
	&NewStructOps,
	"GBAGameplayClampedAttributeData",
	Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::PropPointers),
	sizeof(FGBAGameplayClampedAttributeData),
	alignof(FGBAGameplayClampedAttributeData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData()
{
	if (!Z_Registration_Info_UScriptStruct_GBAGameplayClampedAttributeData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GBAGameplayClampedAttributeData.InnerSingleton, Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GBAGameplayClampedAttributeData.InnerSingleton;
}
// End ScriptStruct FGBAGameplayClampedAttributeData

// Begin Class UGBAAttributeSetBlueprintBase Function ClampAttributeValue
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics
{
	struct GBAAttributeSetBlueprintBase_eventClampAttributeValue_Parms
	{
		FGameplayAttribute Attribute;
		float MinValue;
		float MaxValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * Clamps the Attribute from MinValue to MaxValue\n\x09 *\n\x09 * @param Attribute Gameplay Attribute to clamp the value\n\x09 * @param MinValue The lower bound float to clamp the value within\n\x09 * @param MaxValue The higher bound float to clamp the value within\n\x09 */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Clamps the Attribute from MinValue to MaxValue\n\n@param Attribute Gameplay Attribute to clamp the value\n@param MinValue The lower bound float to clamp the value within\n@param MaxValue The higher bound float to clamp the value within" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventClampAttributeValue_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attribute_MetaData), NewProp_Attribute_MetaData) }; // 2792951819
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::NewProp_MinValue = { "MinValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventClampAttributeValue_Parms, MinValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::NewProp_MaxValue = { "MaxValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventClampAttributeValue_Parms, MaxValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::NewProp_Attribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::NewProp_MinValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::NewProp_MaxValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "ClampAttributeValue", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::GBAAttributeSetBlueprintBase_eventClampAttributeValue_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::GBAAttributeSetBlueprintBase_eventClampAttributeValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execClampAttributeValue)
{
	P_GET_STRUCT(FGameplayAttribute,Z_Param_Attribute);
	P_GET_PROPERTY(FFloatProperty,Z_Param_MinValue);
	P_GET_PROPERTY(FFloatProperty,Z_Param_MaxValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClampAttributeValue(Z_Param_Attribute,Z_Param_MinValue,Z_Param_MaxValue);
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function ClampAttributeValue

// Begin Class UGBAAttributeSetBlueprintBase Function HandleRepNotifyForGameplayAttributeData
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics
{
	struct GBAAttributeSetBlueprintBase_eventHandleRepNotifyForGameplayAttributeData_Parms
	{
		FGameplayAttributeData InAttribute;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * To be called from Blueprint rep notifies for a given Gameplay Attribute Data member variable.\n\x09 *\n\x09 * Meant to provide the same prediction capabilities of GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Attribute, OldAttribute) macro that is usually\n\x09 * called from within a C++ AttributeSet rep notify handler.\n\x09 *\n\x09 * @param InAttribute The Gameplay Attribute Data property to handle rep notify for. Simply wire in the appropriate\n\x09 * Blueprint member Attribute variable for the rep notify you're implementing.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "To be called from Blueprint rep notifies for a given Gameplay Attribute Data member variable.\n\nMeant to provide the same prediction capabilities of GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Attribute, OldAttribute) macro that is usually\ncalled from within a C++ AttributeSet rep notify handler.\n\n@param InAttribute The Gameplay Attribute Data property to handle rep notify for. Simply wire in the appropriate\nBlueprint member Attribute variable for the rep notify you're implementing." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventHandleRepNotifyForGameplayAttributeData_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 675369593
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::NewProp_InAttribute,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "HandleRepNotifyForGameplayAttributeData", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::GBAAttributeSetBlueprintBase_eventHandleRepNotifyForGameplayAttributeData_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::GBAAttributeSetBlueprintBase_eventHandleRepNotifyForGameplayAttributeData_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execHandleRepNotifyForGameplayAttributeData)
{
	P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_InAttribute);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleRepNotifyForGameplayAttributeData(Z_Param_Out_InAttribute);
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function HandleRepNotifyForGameplayAttributeData

// Begin Class UGBAAttributeSetBlueprintBase Function HandleRepNotifyForGameplayClampedAttributeData
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics
{
	struct GBAAttributeSetBlueprintBase_eventHandleRepNotifyForGameplayClampedAttributeData_Parms
	{
		FGBAGameplayClampedAttributeData InAttribute;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * To be called from Blueprint rep notifies for a given (Clamped) Gameplay Attribute Data member variable.\n\x09 *\n\x09 * Meant to provide the same prediction capabilities of GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Attribute, OldAttribute) macro that is usually\n\x09 * called from within a C++ AttributeSet rep notify handler.\n\x09 * \n\x09 * @param InAttribute The Gameplay Attribute Data property to handle rep notify for. Simply wire in the appropriate\n\x09 * Blueprint member Attribute variable for the rep notify you're implementing.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "To be called from Blueprint rep notifies for a given (Clamped) Gameplay Attribute Data member variable.\n\nMeant to provide the same prediction capabilities of GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Attribute, OldAttribute) macro that is usually\ncalled from within a C++ AttributeSet rep notify handler.\n\n@param InAttribute The Gameplay Attribute Data property to handle rep notify for. Simply wire in the appropriate\nBlueprint member Attribute variable for the rep notify you're implementing." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventHandleRepNotifyForGameplayClampedAttributeData_Parms, InAttribute), Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 1340368909
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::NewProp_InAttribute,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "HandleRepNotifyForGameplayClampedAttributeData", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::GBAAttributeSetBlueprintBase_eventHandleRepNotifyForGameplayClampedAttributeData_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::GBAAttributeSetBlueprintBase_eventHandleRepNotifyForGameplayClampedAttributeData_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execHandleRepNotifyForGameplayClampedAttributeData)
{
	P_GET_STRUCT_REF(FGBAGameplayClampedAttributeData,Z_Param_Out_InAttribute);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleRepNotifyForGameplayClampedAttributeData(Z_Param_Out_InAttribute);
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function HandleRepNotifyForGameplayClampedAttributeData

// Begin Class UGBAAttributeSetBlueprintBase Function K2_GetActorInfo
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics
{
	struct GBAAttributeSetBlueprintBase_eventK2_GetActorInfo_Parms
	{
		FGameplayAbilityActorInfo ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * Returns the Owner's Ability System Component cached data about the owning actor that abilities will need to frequently access\n\x09 * (movement component, mesh component, anim instance, etc)\n\x09 */" },
		{ "DisplayName", "GetActorInfo" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Returns the Owner's Ability System Component cached data about the owning actor that abilities will need to frequently access\n(movement component, mesh component, anim instance, etc)" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010008000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_GetActorInfo_Parms, ReturnValue), Z_Construct_UScriptStruct_FGameplayAbilityActorInfo, METADATA_PARAMS(0, nullptr) }; // 3720176897
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_GetActorInfo", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::GBAAttributeSetBlueprintBase_eventK2_GetActorInfo_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::GBAAttributeSetBlueprintBase_eventK2_GetActorInfo_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execK2_GetActorInfo)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGameplayAbilityActorInfo*)Z_Param__Result=P_THIS->K2_GetActorInfo();
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_GetActorInfo

// Begin Class UGBAAttributeSetBlueprintBase Function K2_GetAttributeBaseValue
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics
{
	struct GBAAttributeSetBlueprintBase_eventK2_GetAttributeBaseValue_Parms
	{
		FGameplayAttribute Attribute;
		bool bSuccessfullyFoundAttribute;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * Returns the *base* (as opposed to current) value of an Attribute.\n\x09 *\n\x09 * @param Attribute The Gameplay Attribute we want to get the base value\n\x09 * @param bSuccessfullyFoundAttribute Return value indicating whether the value was retrieved successfully\n\x09 * (false if owning ASC is invalid or if the AttributeSet the input Attribute belong to is not granted)\n\x09 *\n\x09 * @return Base Value for the Gameplay Attribute\n\x09 */" },
		{ "DisplayName", "GetAttributeBaseValue" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Returns the *base* (as opposed to current) value of an Attribute.\n\n@param Attribute The Gameplay Attribute we want to get the base value\n@param bSuccessfullyFoundAttribute Return value indicating whether the value was retrieved successfully\n(false if owning ASC is invalid or if the AttributeSet the input Attribute belong to is not granted)\n\n@return Base Value for the Gameplay Attribute" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attribute;
	static void NewProp_bSuccessfullyFoundAttribute_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccessfullyFoundAttribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_GetAttributeBaseValue_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(0, nullptr) }; // 2792951819
void Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::NewProp_bSuccessfullyFoundAttribute_SetBit(void* Obj)
{
	((GBAAttributeSetBlueprintBase_eventK2_GetAttributeBaseValue_Parms*)Obj)->bSuccessfullyFoundAttribute = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::NewProp_bSuccessfullyFoundAttribute = { "bSuccessfullyFoundAttribute", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GBAAttributeSetBlueprintBase_eventK2_GetAttributeBaseValue_Parms), &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::NewProp_bSuccessfullyFoundAttribute_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_GetAttributeBaseValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::NewProp_Attribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::NewProp_bSuccessfullyFoundAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_GetAttributeBaseValue", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::GBAAttributeSetBlueprintBase_eventK2_GetAttributeBaseValue_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::GBAAttributeSetBlueprintBase_eventK2_GetAttributeBaseValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execK2_GetAttributeBaseValue)
{
	P_GET_STRUCT(FGameplayAttribute,Z_Param_Attribute);
	P_GET_UBOOL_REF(Z_Param_Out_bSuccessfullyFoundAttribute);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->K2_GetAttributeBaseValue(Z_Param_Attribute,Z_Param_Out_bSuccessfullyFoundAttribute);
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_GetAttributeBaseValue

// Begin Class UGBAAttributeSetBlueprintBase Function K2_GetAttributeValue
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics
{
	struct GBAAttributeSetBlueprintBase_eventK2_GetAttributeValue_Parms
	{
		FGameplayAttribute Attribute;
		bool bSuccessfullyFoundAttribute;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * Returns the *current* (as opposed to base) value of an Attribute.\n\x09 *\n\x09 * @param Attribute The Gameplay Attribute we want to get the current value\n\x09 * @param bSuccessfullyFoundAttribute Return value indicating whether the value was retrieved successfully\n\x09 * (false if owning ASC is invalid or if the AttributeSet the input Attribute belong to is not granted)\n\x09 *\n\x09 * @return Current Value for the Gameplay Attribute\n\x09 */" },
		{ "DisplayName", "GetAttributeValue" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Returns the *current* (as opposed to base) value of an Attribute.\n\n@param Attribute The Gameplay Attribute we want to get the current value\n@param bSuccessfullyFoundAttribute Return value indicating whether the value was retrieved successfully\n(false if owning ASC is invalid or if the AttributeSet the input Attribute belong to is not granted)\n\n@return Current Value for the Gameplay Attribute" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attribute;
	static void NewProp_bSuccessfullyFoundAttribute_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccessfullyFoundAttribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_GetAttributeValue_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(0, nullptr) }; // 2792951819
void Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::NewProp_bSuccessfullyFoundAttribute_SetBit(void* Obj)
{
	((GBAAttributeSetBlueprintBase_eventK2_GetAttributeValue_Parms*)Obj)->bSuccessfullyFoundAttribute = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::NewProp_bSuccessfullyFoundAttribute = { "bSuccessfullyFoundAttribute", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GBAAttributeSetBlueprintBase_eventK2_GetAttributeValue_Parms), &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::NewProp_bSuccessfullyFoundAttribute_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_GetAttributeValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::NewProp_Attribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::NewProp_bSuccessfullyFoundAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_GetAttributeValue", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::GBAAttributeSetBlueprintBase_eventK2_GetAttributeValue_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::GBAAttributeSetBlueprintBase_eventK2_GetAttributeValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execK2_GetAttributeValue)
{
	P_GET_STRUCT(FGameplayAttribute,Z_Param_Attribute);
	P_GET_UBOOL_REF(Z_Param_Out_bSuccessfullyFoundAttribute);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->K2_GetAttributeValue(Z_Param_Attribute,Z_Param_Out_bSuccessfullyFoundAttribute);
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_GetAttributeValue

// Begin Class UGBAAttributeSetBlueprintBase Function K2_GetOwningAbilitySystemComponent
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics
{
	struct GBAAttributeSetBlueprintBase_eventK2_GetOwningAbilitySystemComponent_Parms
	{
		UAbilitySystemComponent* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** Returns the Ability System Component of the Owning Actor */" },
		{ "DisplayName", "GetOwningAbilitySystemComponent" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Returns the Ability System Component of the Owning Actor" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_GetOwningAbilitySystemComponent_Parms, ReturnValue), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_GetOwningAbilitySystemComponent", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::GBAAttributeSetBlueprintBase_eventK2_GetOwningAbilitySystemComponent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::GBAAttributeSetBlueprintBase_eventK2_GetOwningAbilitySystemComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execK2_GetOwningAbilitySystemComponent)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UAbilitySystemComponent**)Z_Param__Result=P_THIS->K2_GetOwningAbilitySystemComponent();
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_GetOwningAbilitySystemComponent

// Begin Class UGBAAttributeSetBlueprintBase Function K2_GetOwningActor
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics
{
	struct GBAAttributeSetBlueprintBase_eventK2_GetOwningActor_Parms
	{
		AActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/** Gets information about owning actor */" },
		{ "DisplayName", "GetOwningActor" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Gets information about owning actor" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_GetOwningActor_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_GetOwningActor", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::GBAAttributeSetBlueprintBase_eventK2_GetOwningActor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::GBAAttributeSetBlueprintBase_eventK2_GetOwningActor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execK2_GetOwningActor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(AActor**)Z_Param__Result=P_THIS->K2_GetOwningActor();
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_GetOwningActor

// Begin Class UGBAAttributeSetBlueprintBase Function K2_PostAttributeBaseChange
struct GBAAttributeSetBlueprintBase_eventK2_PostAttributeBaseChange_Parms
{
	FGameplayAttribute InAttribute;
	float OldValue;
	float NewValue;
};
static FName NAME_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange = FName(TEXT("K2_PostAttributeBaseChange"));
void UGBAAttributeSetBlueprintBase::K2_PostAttributeBaseChange(FGameplayAttribute const& InAttribute, float OldValue, float NewValue) const
{
	GBAAttributeSetBlueprintBase_eventK2_PostAttributeBaseChange_Parms Parms;
	Parms.InAttribute=InAttribute;
	Parms.OldValue=OldValue;
	Parms.NewValue=NewValue;
	const_cast<UGBAAttributeSetBlueprintBase*>(this)->ProcessEvent(FindFunctionChecked(NAME_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange),&Parms);
}
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AttributeSet" },
		{ "Comment", "/**\n\x09 * Called just after any modification happens to an attribute's base value right after aggregation (when an attribute aggregator exists).\n\x09 * \n\x09 * @param InAttribute The Gameplay Attribute whose base value has been changed\n\x09 * @param OldValue Original value for the Gameplay Attribute, before PreAttributeBaseChange event and actual modification happened\n\x09 * @param NewValue New value for the Gameplay Attribute, after PreAttributeBaseChange event and modification\n\x09 */" },
		{ "DisplayName", "PostAttributeBaseChange" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Called just after any modification happens to an attribute's base value right after aggregation (when an attribute aggregator exists).\n\n@param InAttribute The Gameplay Attribute whose base value has been changed\n@param OldValue Original value for the Gameplay Attribute, before PreAttributeBaseChange event and actual modification happened\n@param NewValue New value for the Gameplay Attribute, after PreAttributeBaseChange event and modification" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OldValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PostAttributeBaseChange_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 2792951819
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::NewProp_OldValue = { "OldValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PostAttributeBaseChange_Parms, OldValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::NewProp_NewValue = { "NewValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PostAttributeBaseChange_Parms, NewValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::NewProp_InAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::NewProp_OldValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::NewProp_NewValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_PostAttributeBaseChange", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::PropPointers), sizeof(GBAAttributeSetBlueprintBase_eventK2_PostAttributeBaseChange_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x48420800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::Function_MetaDataParams) };
static_assert(sizeof(GBAAttributeSetBlueprintBase_eventK2_PostAttributeBaseChange_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_PostAttributeBaseChange

// Begin Class UGBAAttributeSetBlueprintBase Function K2_PostAttributeChange
struct GBAAttributeSetBlueprintBase_eventK2_PostAttributeChange_Parms
{
	FGameplayAttribute Attribute;
	float OldValue;
	float NewValue;
};
static FName NAME_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange = FName(TEXT("K2_PostAttributeChange"));
void UGBAAttributeSetBlueprintBase::K2_PostAttributeChange(FGameplayAttribute const& Attribute, float OldValue, float NewValue)
{
	GBAAttributeSetBlueprintBase_eventK2_PostAttributeChange_Parms Parms;
	Parms.Attribute=Attribute;
	Parms.OldValue=OldValue;
	Parms.NewValue=NewValue;
	ProcessEvent(FindFunctionChecked(NAME_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange),&Parms);
}
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AttributeSet" },
		{ "Comment", "/**\n\x09 * Called just after any modification happens to an attribute.\n\x09 * \n\x09 * @param Attribute The Gameplay Attribute whose value has been changed\n\x09 * @param OldValue Original value for the Gameplay Attribute, before PreAttributeChange event and actual modification happened\n\x09 * @param NewValue New value for the Gameplay Attribute, after PreAttributeChange event and modification\n\x09 */" },
		{ "DisplayName", "PostAttributeChange" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Called just after any modification happens to an attribute.\n\n@param Attribute The Gameplay Attribute whose value has been changed\n@param OldValue Original value for the Gameplay Attribute, before PreAttributeChange event and actual modification happened\n@param NewValue New value for the Gameplay Attribute, after PreAttributeChange event and modification" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OldValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PostAttributeChange_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attribute_MetaData), NewProp_Attribute_MetaData) }; // 2792951819
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::NewProp_OldValue = { "OldValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PostAttributeChange_Parms, OldValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::NewProp_NewValue = { "NewValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PostAttributeChange_Parms, NewValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::NewProp_Attribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::NewProp_OldValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::NewProp_NewValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_PostAttributeChange", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::PropPointers), sizeof(GBAAttributeSetBlueprintBase_eventK2_PostAttributeChange_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08420800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::Function_MetaDataParams) };
static_assert(sizeof(GBAAttributeSetBlueprintBase_eventK2_PostAttributeChange_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_PostAttributeChange

// Begin Class UGBAAttributeSetBlueprintBase Function K2_PostGameplayEffectExecute
struct GBAAttributeSetBlueprintBase_eventK2_PostGameplayEffectExecute_Parms
{
	FGameplayAttribute Attribute;
	FGBAAttributeSetExecutionData Data;
};
static FName NAME_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute = FName(TEXT("K2_PostGameplayEffectExecute"));
void UGBAAttributeSetBlueprintBase::K2_PostGameplayEffectExecute(FGameplayAttribute const& Attribute, FGBAAttributeSetExecutionData const& Data)
{
	GBAAttributeSetBlueprintBase_eventK2_PostGameplayEffectExecute_Parms Parms;
	Parms.Attribute=Attribute;
	Parms.Data=Data;
	ProcessEvent(FindFunctionChecked(NAME_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute),&Parms);
}
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AttributeSet" },
		{ "Comment", "/**\n\x09 * Called just after a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made.\n\x09 * \n\x09 * Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute.\n\x09 * It is not called during an application of a GameplayEffect, such as a 5 second +10 movement speed buff.\n\x09 *\n\x09 * This should apply 'gamewide' rules. Such as clamping Health to MaxHealth or granting +3 health for every point of strength, etc\n\x09 *\n\x09 * @param Attribute The Gameplay Attribute whose value has been changed by a Gameplay Effect\n\x09 * @param Data Payload with information extracted from FGameplayEffectModCallbackData, the Source / Target actor, Ability System Component,\n\x09 * Controllers, Effect Context, Specs and Source Tags, Magnitude and Delta values, etc.\n\x09 */" },
		{ "DisplayName", "PostGameplayEffectExecute" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Called just after a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made.\n\nNote this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute.\nIt is not called during an application of a GameplayEffect, such as a 5 second +10 movement speed buff.\n\nThis should apply 'gamewide' rules. Such as clamping Health to MaxHealth or granting +3 health for every point of strength, etc\n\n@param Attribute The Gameplay Attribute whose value has been changed by a Gameplay Effect\n@param Data Payload with information extracted from FGameplayEffectModCallbackData, the Source / Target actor, Ability System Component,\nControllers, Effect Context, Specs and Source Tags, Magnitude and Delta values, etc." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attribute_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attribute;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Data;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PostGameplayEffectExecute_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attribute_MetaData), NewProp_Attribute_MetaData) }; // 2792951819
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PostGameplayEffectExecute_Parms, Data), Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Data_MetaData), NewProp_Data_MetaData) }; // 754966430
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::NewProp_Attribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::NewProp_Data,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_PostGameplayEffectExecute", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::PropPointers), sizeof(GBAAttributeSetBlueprintBase_eventK2_PostGameplayEffectExecute_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08420800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::Function_MetaDataParams) };
static_assert(sizeof(GBAAttributeSetBlueprintBase_eventK2_PostGameplayEffectExecute_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_PostGameplayEffectExecute

// Begin Class UGBAAttributeSetBlueprintBase Function K2_PreAttributeBaseChange
struct GBAAttributeSetBlueprintBase_eventK2_PreAttributeBaseChange_Parms
{
	FGameplayAttribute InAttribute;
	float InValue;
	float OutValue;
};
static FName NAME_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange = FName(TEXT("K2_PreAttributeBaseChange"));
void UGBAAttributeSetBlueprintBase::K2_PreAttributeBaseChange(FGameplayAttribute const& InAttribute, float InValue, float& OutValue) const
{
	GBAAttributeSetBlueprintBase_eventK2_PreAttributeBaseChange_Parms Parms;
	Parms.InAttribute=InAttribute;
	Parms.InValue=InValue;
	Parms.OutValue=OutValue;
	const_cast<UGBAAttributeSetBlueprintBase*>(this)->ProcessEvent(FindFunctionChecked(NAME_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange),&Parms);
	OutValue=Parms.OutValue;
}
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AttributeSet" },
		{ "Comment", "/**\n\x09 * This is called just before any modification happens to an attribute's base value when an attribute aggregator exists.\n\x09 * This function should enforce clamping (presuming you wish to clamp the base value along with the final value in PreAttributeChange)\n\x09 * This function should NOT invoke gameplay related events or callbacks. Do those in PreAttributeChange() which will be called prior to the\n\x09 * final value of the attribute actually changing.\n\x09 *\n\x09 * @param InAttribute The Gameplay Attribute whose base value is about to change\n\x09 * @param InValue Original value for the Gameplay Attribute\n\x09 * @param OutValue Return value of the function which represents the new base value for the Gameplay Attribute\n\x09 */" },
		{ "DisplayName", "PreAttributeBaseChange" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "This is called just before any modification happens to an attribute's base value when an attribute aggregator exists.\nThis function should enforce clamping (presuming you wish to clamp the base value along with the final value in PreAttributeChange)\nThis function should NOT invoke gameplay related events or callbacks. Do those in PreAttributeChange() which will be called prior to the\nfinal value of the attribute actually changing.\n\n@param InAttribute The Gameplay Attribute whose base value is about to change\n@param InValue Original value for the Gameplay Attribute\n@param OutValue Return value of the function which represents the new base value for the Gameplay Attribute" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OutValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PreAttributeBaseChange_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 2792951819
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PreAttributeBaseChange_Parms, InValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::NewProp_OutValue = { "OutValue", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PreAttributeBaseChange_Parms, OutValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::NewProp_InAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::NewProp_InValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::NewProp_OutValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_PreAttributeBaseChange", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::PropPointers), sizeof(GBAAttributeSetBlueprintBase_eventK2_PreAttributeBaseChange_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x48420800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::Function_MetaDataParams) };
static_assert(sizeof(GBAAttributeSetBlueprintBase_eventK2_PreAttributeBaseChange_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_PreAttributeBaseChange

// Begin Class UGBAAttributeSetBlueprintBase Function K2_PreAttributeChange
struct GBAAttributeSetBlueprintBase_eventK2_PreAttributeChange_Parms
{
	FGameplayAttribute InAttribute;
	float InValue;
	float OutValue;
};
static FName NAME_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange = FName(TEXT("K2_PreAttributeChange"));
void UGBAAttributeSetBlueprintBase::K2_PreAttributeChange(FGameplayAttribute const& InAttribute, float InValue, float& OutValue)
{
	GBAAttributeSetBlueprintBase_eventK2_PreAttributeChange_Parms Parms;
	Parms.InAttribute=InAttribute;
	Parms.InValue=InValue;
	Parms.OutValue=OutValue;
	ProcessEvent(FindFunctionChecked(NAME_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange),&Parms);
	OutValue=Parms.OutValue;
}
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AttributeSet" },
		{ "Comment", "/**\n\x09 * Called just before any modification happens to an attribute. This is lower level than PreAttributeModify/PostAttribute modify.\n\x09 * \n\x09 * There is no additional context provided here since anything can trigger this.\n\x09 * Executed effects, duration based effects, effects being removed, immunity being applied, stacking rules changing, etc.\n\x09 * \n\x09 * This function is meant to enforce things like \"Health = Clamp(Health, 0, MaxHealth)\" and NOT things like\n\x09 * \"trigger this extra thing if damage is applied, etc\".\n\x09 * \n\x09 * OutValue is a mutable reference so you are able to clamp the newly applied value as well (**Note** When overriding in BP,\n\x09 * this is the return value of the BP function, make sure to pass in the new value. Typical implementation should simply\n\x09 * return the input value parameter)\n\x09 *\n\x09 * @param InAttribute The Gameplay Attribute whose value is about to change\n\x09 * @param InValue Original value for the Gameplay Attribute\n\x09 * @param OutValue Return value of the function which represents the new value for the Gameplay Attribute\n\x09 */" },
		{ "DisplayName", "PreAttributeChange" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Called just before any modification happens to an attribute. This is lower level than PreAttributeModify/PostAttribute modify.\n\nThere is no additional context provided here since anything can trigger this.\nExecuted effects, duration based effects, effects being removed, immunity being applied, stacking rules changing, etc.\n\nThis function is meant to enforce things like \"Health = Clamp(Health, 0, MaxHealth)\" and NOT things like\n\"trigger this extra thing if damage is applied, etc\".\n\nOutValue is a mutable reference so you are able to clamp the newly applied value as well (**Note** When overriding in BP,\nthis is the return value of the BP function, make sure to pass in the new value. Typical implementation should simply\nreturn the input value parameter)\n\n@param InAttribute The Gameplay Attribute whose value is about to change\n@param InValue Original value for the Gameplay Attribute\n@param OutValue Return value of the function which represents the new value for the Gameplay Attribute" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OutValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PreAttributeChange_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 2792951819
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::NewProp_InValue = { "InValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PreAttributeChange_Parms, InValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::NewProp_OutValue = { "OutValue", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PreAttributeChange_Parms, OutValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::NewProp_InAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::NewProp_InValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::NewProp_OutValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_PreAttributeChange", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::PropPointers), sizeof(GBAAttributeSetBlueprintBase_eventK2_PreAttributeChange_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08420800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::Function_MetaDataParams) };
static_assert(sizeof(GBAAttributeSetBlueprintBase_eventK2_PreAttributeChange_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_PreAttributeChange

// Begin Class UGBAAttributeSetBlueprintBase Function K2_PreGameplayEffectExecute
struct GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms
{
	FGameplayAttribute InAttribute;
	FGBAAttributeSetExecutionData InData;
	bool ReturnValue;

	/** Constructor, initializes return property only **/
	GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms()
		: ReturnValue(false)
	{
	}
};
static FName NAME_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute = FName(TEXT("K2_PreGameplayEffectExecute"));
bool UGBAAttributeSetBlueprintBase::K2_PreGameplayEffectExecute(FGameplayAttribute const& InAttribute, FGBAAttributeSetExecutionData const& InData)
{
	GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms Parms;
	Parms.InAttribute=InAttribute;
	Parms.InData=InData;
	ProcessEvent(FindFunctionChecked(NAME_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute),&Parms);
	return !!Parms.ReturnValue;
}
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AttributeSet" },
		{ "Comment", "/**\n\x09 * Called just before modifying the value of an attribute. AttributeSet can make additional modifications here.\n\x09 *\n\x09 * Return true to continue, or false to throw out the modification\n\x09 * \n\x09 * Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute.\n\x09 * It is not called during an application of a GameplayEffect, such as a 5 second +10 movement speed buff.\n\x09 *\n\x09 * This should apply 'gamewide' rules. Such as clamping Health to MaxHealth or granting +3 health for every point of strength, etc\n\x09 * PreGameplayEffectExecute can return false to 'throw out' this modification.\n\x09 * \n\x09 * (**Note** When overriding this function in BP, make sure to return true, otherwise the Gameplay Effects won't apply anymore. As the default\n\x09 * behavior for the editor is to implement the method with return value set to false, this is something to be wary off.)\n\x09 *\n\x09 * @param InAttribute The Gameplay Attribute whose value is about to be changed by a Gameplay Effect\n\x09 * @param InData Payload with information extracted from FGameplayEffectModCallbackData, the Source / Target actor, Ability System Component,\n\x09 * Controllers, Effect Context, Specs and Source Tags, Magnitude and Delta values, etc.\n\x09 *\n\x09 * @return Return true to continue, or false to throw out the modification.\n\x09 */" },
		{ "DisplayName", "PreGameplayEffectExecute" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Called just before modifying the value of an attribute. AttributeSet can make additional modifications here.\n\nReturn true to continue, or false to throw out the modification\n\nNote this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute.\nIt is not called during an application of a GameplayEffect, such as a 5 second +10 movement speed buff.\n\nThis should apply 'gamewide' rules. Such as clamping Health to MaxHealth or granting +3 health for every point of strength, etc\nPreGameplayEffectExecute can return false to 'throw out' this modification.\n\n(**Note** When overriding this function in BP, make sure to return true, otherwise the Gameplay Effects won't apply anymore. As the default\nbehavior for the editor is to implement the method with return value set to false, this is something to be wary off.)\n\n@param InAttribute The Gameplay Attribute whose value is about to be changed by a Gameplay Effect\n@param InData Payload with information extracted from FGameplayEffectModCallbackData, the Source / Target actor, Ability System Component,\nControllers, Effect Context, Specs and Source Tags, Magnitude and Delta values, etc.\n\n@return Return true to continue, or false to throw out the modification." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_InAttribute;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InData;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::NewProp_InAttribute = { "InAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms, InAttribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InAttribute_MetaData), NewProp_InAttribute_MetaData) }; // 2792951819
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::NewProp_InData = { "InData", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms, InData), Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InData_MetaData), NewProp_InData_MetaData) }; // 754966430
void Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms), &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::NewProp_InAttribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::NewProp_InData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_PreGameplayEffectExecute", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::PropPointers), sizeof(GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08420C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::Function_MetaDataParams) };
static_assert(sizeof(GBAAttributeSetBlueprintBase_eventK2_PreGameplayEffectExecute_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execK2_PreGameplayEffectExecute)
{
	P_GET_STRUCT_REF(FGameplayAttribute,Z_Param_Out_InAttribute);
	P_GET_STRUCT_REF(FGBAAttributeSetExecutionData,Z_Param_Out_InData);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->K2_PreGameplayEffectExecute_Implementation(Z_Param_Out_InAttribute,Z_Param_Out_InData);
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_PreGameplayEffectExecute

// Begin Class UGBAAttributeSetBlueprintBase Function K2_SetAttributeValue
struct Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics
{
	struct GBAAttributeSetBlueprintBase_eventK2_SetAttributeValue_Parms
	{
		FGameplayAttribute Attribute;
		float NewValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes" },
		{ "Comment", "/**\n\x09 * Sets the *base* (as opposed to current) value of an Attribute.\n\x09 *\n\x09 * @param Attribute The Gameplay Attribute we want to set the base value\n\x09 * @param NewValue Float value to set\n\x09 */" },
		{ "DisplayName", "SetAttributeValue" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ToolTip", "Sets the *base* (as opposed to current) value of an Attribute.\n\n@param Attribute The Gameplay Attribute we want to set the base value\n@param NewValue Float value to set" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Attribute;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_SetAttributeValue_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(0, nullptr) }; // 2792951819
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::NewProp_NewValue = { "NewValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBAAttributeSetBlueprintBase_eventK2_SetAttributeValue_Parms, NewValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::NewProp_Attribute,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::NewProp_NewValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBAAttributeSetBlueprintBase, nullptr, "K2_SetAttributeValue", nullptr, nullptr, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::GBAAttributeSetBlueprintBase_eventK2_SetAttributeValue_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::GBAAttributeSetBlueprintBase_eventK2_SetAttributeValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBAAttributeSetBlueprintBase::execK2_SetAttributeValue)
{
	P_GET_STRUCT(FGameplayAttribute,Z_Param_Attribute);
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->K2_SetAttributeValue(Z_Param_Attribute,Z_Param_NewValue);
	P_NATIVE_END;
}
// End Class UGBAAttributeSetBlueprintBase Function K2_SetAttributeValue

// Begin Class UGBAAttributeSetBlueprintBase
void UGBAAttributeSetBlueprintBase::StaticRegisterNativesUGBAAttributeSetBlueprintBase()
{
	UClass* Class = UGBAAttributeSetBlueprintBase::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ClampAttributeValue", &UGBAAttributeSetBlueprintBase::execClampAttributeValue },
		{ "HandleRepNotifyForGameplayAttributeData", &UGBAAttributeSetBlueprintBase::execHandleRepNotifyForGameplayAttributeData },
		{ "HandleRepNotifyForGameplayClampedAttributeData", &UGBAAttributeSetBlueprintBase::execHandleRepNotifyForGameplayClampedAttributeData },
		{ "K2_GetActorInfo", &UGBAAttributeSetBlueprintBase::execK2_GetActorInfo },
		{ "K2_GetAttributeBaseValue", &UGBAAttributeSetBlueprintBase::execK2_GetAttributeBaseValue },
		{ "K2_GetAttributeValue", &UGBAAttributeSetBlueprintBase::execK2_GetAttributeValue },
		{ "K2_GetOwningAbilitySystemComponent", &UGBAAttributeSetBlueprintBase::execK2_GetOwningAbilitySystemComponent },
		{ "K2_GetOwningActor", &UGBAAttributeSetBlueprintBase::execK2_GetOwningActor },
		{ "K2_PreGameplayEffectExecute", &UGBAAttributeSetBlueprintBase::execK2_PreGameplayEffectExecute },
		{ "K2_SetAttributeValue", &UGBAAttributeSetBlueprintBase::execK2_SetAttributeValue },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBAAttributeSetBlueprintBase);
UClass* Z_Construct_UClass_UGBAAttributeSetBlueprintBase_NoRegister()
{
	return UGBAAttributeSetBlueprintBase::StaticClass();
}
struct Z_Construct_UClass_UGBAAttributeSetBlueprintBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Defines the set of all GameplayAttributes for your game.\n * \n * Games should subclass this and add FGameplayAttributeData properties to represent attributes like health, damage, etc\n * \n * AttributeSets are added to the actors as subobjects, and then registered with the AbilitySystemComponent\n * It is often desired to have several sets per project that inherit from each other\n * You could make a base health set, then have a player set that inherits from it and adds more attributes\n */" },
		{ "DisplayName", "Attribute Set Blueprint Base" },
		{ "IncludePath", "Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ModuleRelativePath", "Public/Abilities/GBAAttributeSetBlueprintBase.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "Defines the set of all GameplayAttributes for your game.\n\nGames should subclass this and add FGameplayAttributeData properties to represent attributes like health, damage, etc\n\nAttributeSets are added to the actors as subobjects, and then registered with the AbilitySystemComponent\nIt is often desired to have several sets per project that inherit from each other\nYou could make a base health set, then have a player set that inherits from it and adds more attributes" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_ClampAttributeValue, "ClampAttributeValue" }, // 376399045
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayAttributeData, "HandleRepNotifyForGameplayAttributeData" }, // 3215636926
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_HandleRepNotifyForGameplayClampedAttributeData, "HandleRepNotifyForGameplayClampedAttributeData" }, // 3229290501
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetActorInfo, "K2_GetActorInfo" }, // 3455850827
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeBaseValue, "K2_GetAttributeBaseValue" }, // 1814865148
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetAttributeValue, "K2_GetAttributeValue" }, // 3652266530
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningAbilitySystemComponent, "K2_GetOwningAbilitySystemComponent" }, // 1758836740
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_GetOwningActor, "K2_GetOwningActor" }, // 413879167
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeBaseChange, "K2_PostAttributeBaseChange" }, // 3056853270
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostAttributeChange, "K2_PostAttributeChange" }, // 496726415
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PostGameplayEffectExecute, "K2_PostGameplayEffectExecute" }, // 3207809301
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeBaseChange, "K2_PreAttributeBaseChange" }, // 3693484538
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreAttributeChange, "K2_PreAttributeChange" }, // 2739138677
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_PreGameplayEffectExecute, "K2_PreGameplayEffectExecute" }, // 3574446218
		{ &Z_Construct_UFunction_UGBAAttributeSetBlueprintBase_K2_SetAttributeValue, "K2_SetAttributeValue" }, // 3838847804
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBAAttributeSetBlueprintBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGBAAttributeSetBlueprintBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAttributeSet,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAAttributeSetBlueprintBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBAAttributeSetBlueprintBase_Statics::ClassParams = {
	&UGBAAttributeSetBlueprintBase::StaticClass,
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
	0x003000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAAttributeSetBlueprintBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBAAttributeSetBlueprintBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBAAttributeSetBlueprintBase()
{
	if (!Z_Registration_Info_UClass_UGBAAttributeSetBlueprintBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBAAttributeSetBlueprintBase.OuterSingleton, Z_Construct_UClass_UGBAAttributeSetBlueprintBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBAAttributeSetBlueprintBase.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UClass* StaticClass<UGBAAttributeSetBlueprintBase>()
{
	return UGBAAttributeSetBlueprintBase::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBAAttributeSetBlueprintBase);
UGBAAttributeSetBlueprintBase::~UGBAAttributeSetBlueprintBase() {}
IMPLEMENT_FSTRUCTUREDARCHIVE_SERIALIZER(UGBAAttributeSetBlueprintBase)
// End Class UGBAAttributeSetBlueprintBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EGBAClampingType_StaticEnum, TEXT("EGBAClampingType"), &Z_Registration_Info_UEnum_EGBAClampingType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3580240750U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FGBAAttributeSetExecutionData::StaticStruct, Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics::NewStructOps, TEXT("GBAAttributeSetExecutionData"), &Z_Registration_Info_UScriptStruct_GBAAttributeSetExecutionData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGBAAttributeSetExecutionData), 754966430U) },
		{ FGBAClampDefinition::StaticStruct, Z_Construct_UScriptStruct_FGBAClampDefinition_Statics::NewStructOps, TEXT("GBAClampDefinition"), &Z_Registration_Info_UScriptStruct_GBAClampDefinition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGBAClampDefinition), 2728223817U) },
		{ FGBAGameplayClampedAttributeData::StaticStruct, Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics::NewStructOps, TEXT("GBAGameplayClampedAttributeData"), &Z_Registration_Info_UScriptStruct_GBAGameplayClampedAttributeData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGBAGameplayClampedAttributeData), 1340368909U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBAAttributeSetBlueprintBase, UGBAAttributeSetBlueprintBase::StaticClass, TEXT("UGBAAttributeSetBlueprintBase"), &Z_Registration_Info_UClass_UGBAAttributeSetBlueprintBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBAAttributeSetBlueprintBase), 4020419324U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_3702516085(TEXT("/Script/BlueprintAttributes"),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
