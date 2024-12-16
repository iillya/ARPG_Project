// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributes/Public/Blueprint/GBAAttributeSetBlueprint.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBAAttributeSetBlueprint() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBAAttributeSetBlueprint();
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBAAttributeSetBlueprint_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBlueprint();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributes();
// End Cross Module References

// Begin Class UGBAAttributeSetBlueprint
void UGBAAttributeSetBlueprint::StaticRegisterNativesUGBAAttributeSetBlueprint()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBAAttributeSetBlueprint);
UClass* Z_Construct_UClass_UGBAAttributeSetBlueprint_NoRegister()
{
	return UGBAAttributeSetBlueprint::StaticClass();
}
struct Z_Construct_UClass_UGBAAttributeSetBlueprint_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * A Gameplay Blueprint Attribute Set is essentially a specialized Blueprint whose graphs control a GAS Attribute Set.\n * \n * The factory should pick this for you automatically.\n * \n * Defines the set of GameplayAttributes for your game.\n * \n * Games should subclass this (in Blueprints) and add FGameplayAttributeData properties to represent attributes like health, damage, etc\n * \n * AttributeSets are then registered with the AbilitySystemComponent. It is often desired to have several sets per project that could inherit\n * from each other. You could make a base health set, then have a player set that inherits from it and adds more attributes.\n */" },
		{ "IncludePath", "Blueprint/GBAAttributeSetBlueprint.h" },
		{ "ModuleRelativePath", "Public/Blueprint/GBAAttributeSetBlueprint.h" },
		{ "ToolTip", "A Gameplay Blueprint Attribute Set is essentially a specialized Blueprint whose graphs control a GAS Attribute Set.\n\nThe factory should pick this for you automatically.\n\nDefines the set of GameplayAttributes for your game.\n\nGames should subclass this (in Blueprints) and add FGameplayAttributeData properties to represent attributes like health, damage, etc\n\nAttributeSets are then registered with the AbilitySystemComponent. It is often desired to have several sets per project that could inherit\nfrom each other. You could make a base health set, then have a player set that inherits from it and adds more attributes." },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBAAttributeSetBlueprint>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGBAAttributeSetBlueprint_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprint,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAAttributeSetBlueprint_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBAAttributeSetBlueprint_Statics::ClassParams = {
	&UGBAAttributeSetBlueprint::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAAttributeSetBlueprint_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBAAttributeSetBlueprint_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBAAttributeSetBlueprint()
{
	if (!Z_Registration_Info_UClass_UGBAAttributeSetBlueprint.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBAAttributeSetBlueprint.OuterSingleton, Z_Construct_UClass_UGBAAttributeSetBlueprint_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBAAttributeSetBlueprint.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UClass* StaticClass<UGBAAttributeSetBlueprint>()
{
	return UGBAAttributeSetBlueprint::StaticClass();
}
UGBAAttributeSetBlueprint::UGBAAttributeSetBlueprint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBAAttributeSetBlueprint);
// End Class UGBAAttributeSetBlueprint

// Begin Registration
struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Blueprint_GBAAttributeSetBlueprint_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBAAttributeSetBlueprint, UGBAAttributeSetBlueprint::StaticClass, TEXT("UGBAAttributeSetBlueprint"), &Z_Registration_Info_UClass_UGBAAttributeSetBlueprint, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBAAttributeSetBlueprint), 3522576637U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Blueprint_GBAAttributeSetBlueprint_h_3104568906(TEXT("/Script/BlueprintAttributes"),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Blueprint_GBAAttributeSetBlueprint_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Blueprint_GBAAttributeSetBlueprint_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
