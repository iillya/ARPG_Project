// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributesDeveloper/Public/BlueprintGraph/GBAK2Node_SwitchGameplayAttribute.h"
#include "GameplayAbilities/Public/AttributeSet.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBAK2Node_SwitchGameplayAttribute() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTESDEVELOPER_API UClass* Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute();
BLUEPRINTATTRIBUTESDEVELOPER_API UClass* Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_NoRegister();
BLUEPRINTGRAPH_API UClass* Z_Construct_UClass_UK2Node_Switch();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttribute();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributesDeveloper();
// End Cross Module References

// Begin Class UGBAK2Node_SwitchGameplayAttribute
void UGBAK2Node_SwitchGameplayAttribute::StaticRegisterNativesUGBAK2Node_SwitchGameplayAttribute()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBAK2Node_SwitchGameplayAttribute);
UClass* Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_NoRegister()
{
	return UGBAK2Node_SwitchGameplayAttribute::StaticClass();
}
struct Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Switch Switch on Gameplay Attribute node\n */" },
		{ "IncludePath", "BlueprintGraph/GBAK2Node_SwitchGameplayAttribute.h" },
		{ "ModuleRelativePath", "Public/BlueprintGraph/GBAK2Node_SwitchGameplayAttribute.h" },
		{ "ToolTip", "Switch Switch on Gameplay Attribute node" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinAttributes_MetaData[] = {
		{ "Category", "PinOptions" },
		{ "ModuleRelativePath", "Public/BlueprintGraph/GBAK2Node_SwitchGameplayAttribute.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinNames_MetaData[] = {
		{ "ModuleRelativePath", "Public/BlueprintGraph/GBAK2Node_SwitchGameplayAttribute.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_PinAttributes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PinAttributes;
	static const UECodeGen_Private::FNamePropertyParams NewProp_PinNames_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PinNames;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBAK2Node_SwitchGameplayAttribute>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::NewProp_PinAttributes_Inner = { "PinAttributes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(0, nullptr) }; // 2792951819
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::NewProp_PinAttributes = { "PinAttributes", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBAK2Node_SwitchGameplayAttribute, PinAttributes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinAttributes_MetaData), NewProp_PinAttributes_MetaData) }; // 2792951819
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::NewProp_PinNames_Inner = { "PinNames", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::NewProp_PinNames = { "PinNames", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBAK2Node_SwitchGameplayAttribute, PinNames), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinNames_MetaData), NewProp_PinNames_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::NewProp_PinAttributes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::NewProp_PinAttributes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::NewProp_PinNames_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::NewProp_PinNames,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UK2Node_Switch,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributesDeveloper,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::ClassParams = {
	&UGBAK2Node_SwitchGameplayAttribute::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::PropPointers),
	0,
	0x000800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute()
{
	if (!Z_Registration_Info_UClass_UGBAK2Node_SwitchGameplayAttribute.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBAK2Node_SwitchGameplayAttribute.OuterSingleton, Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBAK2Node_SwitchGameplayAttribute.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTESDEVELOPER_API UClass* StaticClass<UGBAK2Node_SwitchGameplayAttribute>()
{
	return UGBAK2Node_SwitchGameplayAttribute::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBAK2Node_SwitchGameplayAttribute);
UGBAK2Node_SwitchGameplayAttribute::~UGBAK2Node_SwitchGameplayAttribute() {}
// End Class UGBAK2Node_SwitchGameplayAttribute

// Begin Registration
struct Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesDeveloper_Public_BlueprintGraph_GBAK2Node_SwitchGameplayAttribute_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBAK2Node_SwitchGameplayAttribute, UGBAK2Node_SwitchGameplayAttribute::StaticClass, TEXT("UGBAK2Node_SwitchGameplayAttribute"), &Z_Registration_Info_UClass_UGBAK2Node_SwitchGameplayAttribute, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBAK2Node_SwitchGameplayAttribute), 2480727223U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesDeveloper_Public_BlueprintGraph_GBAK2Node_SwitchGameplayAttribute_h_727659656(TEXT("/Script/BlueprintAttributesDeveloper"),
	Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesDeveloper_Public_BlueprintGraph_GBAK2Node_SwitchGameplayAttribute_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesDeveloper_Public_BlueprintGraph_GBAK2Node_SwitchGameplayAttribute_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
