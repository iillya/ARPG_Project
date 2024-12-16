// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributesEditor/Public/AssetTypes/GBABlueprintFactory.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBABlueprintFactory() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTESEDITOR_API UClass* Z_Construct_UClass_UGBABlueprintFactory();
BLUEPRINTATTRIBUTESEDITOR_API UClass* Z_Construct_UClass_UGBABlueprintFactory_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UBlueprintFactory();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributesEditor();
// End Cross Module References

// Begin Class UGBABlueprintFactory
void UGBABlueprintFactory::StaticRegisterNativesUGBABlueprintFactory()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBABlueprintFactory);
UClass* Z_Construct_UClass_UGBABlueprintFactory_NoRegister()
{
	return UGBABlueprintFactory::StaticClass();
}
struct Z_Construct_UClass_UGBABlueprintFactory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Object Object" },
		{ "IncludePath", "AssetTypes/GBABlueprintFactory.h" },
		{ "ModuleRelativePath", "Public/AssetTypes/GBABlueprintFactory.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBABlueprintFactory>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGBABlueprintFactory_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFactory,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributesEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBABlueprintFactory_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBABlueprintFactory_Statics::ClassParams = {
	&UGBABlueprintFactory::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000820A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBABlueprintFactory_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBABlueprintFactory_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBABlueprintFactory()
{
	if (!Z_Registration_Info_UClass_UGBABlueprintFactory.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBABlueprintFactory.OuterSingleton, Z_Construct_UClass_UGBABlueprintFactory_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBABlueprintFactory.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTESEDITOR_API UClass* StaticClass<UGBABlueprintFactory>()
{
	return UGBABlueprintFactory::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBABlueprintFactory);
UGBABlueprintFactory::~UGBABlueprintFactory() {}
// End Class UGBABlueprintFactory

// Begin Registration
struct Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_AssetTypes_GBABlueprintFactory_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBABlueprintFactory, UGBABlueprintFactory::StaticClass, TEXT("UGBABlueprintFactory"), &Z_Registration_Info_UClass_UGBABlueprintFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBABlueprintFactory), 674566801U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_AssetTypes_GBABlueprintFactory_h_2054009933(TEXT("/Script/BlueprintAttributesEditor"),
	Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_AssetTypes_GBABlueprintFactory_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_AssetTypes_GBABlueprintFactory_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
