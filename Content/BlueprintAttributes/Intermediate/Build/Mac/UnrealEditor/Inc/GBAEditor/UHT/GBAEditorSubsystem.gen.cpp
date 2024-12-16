// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributesEditor/Public/Subsystems/GBAEditorSubsystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBAEditorSubsystem() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTESEDITOR_API UClass* Z_Construct_UClass_UGBAEditorSubsystem();
BLUEPRINTATTRIBUTESEDITOR_API UClass* Z_Construct_UClass_UGBAEditorSubsystem_NoRegister();
EDITORSUBSYSTEM_API UClass* Z_Construct_UClass_UEditorSubsystem();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributesEditor();
// End Cross Module References

// Begin Class UGBAEditorSubsystem
void UGBAEditorSubsystem::StaticRegisterNativesUGBAEditorSubsystem()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBAEditorSubsystem);
UClass* Z_Construct_UClass_UGBAEditorSubsystem_NoRegister()
{
	return UGBAEditorSubsystem::StaticClass();
}
struct Z_Construct_UClass_UGBAEditorSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Editor subsystem to handle Gameplay Attribute property renames in Blueprint.\n *\n * Changing a variable name needs to be handled to prevent crash from happening if any Gameplay Effects is using it, and if\n * that Gameplay Effect was previously opened and focused again in editor (not relevant anymore since rework into using TWeakFieldPtr<FProperty>).\n *\n * The Details customization for the Attribute or Effect using those needs to be updated \"live\", whereas in the usual case\n * of having Attributes defined in cpp, code needs to be recompiled and editor restarted.\n *\n * With Blueprints, we need a way to rename attributes and have Gameplay Effects (or other K2 nodes using Gameplay Attribute) updated\n * to reference the new property.\n *\n * ---\n *\n * Subsystem register to an OnVariableRename delegate fired off from `UGBAAttributeSetBlueprint`, and handle any editor specific code.\n *\n * When a rename happens, this event fires off and triggers the following logic in this subsystem:\n *\n * 1. Get all referencers to the original Attribute Set Blueprints (its package name)\n * 2. Check if any referencers is currently opened in Editor, store them\n * (TODO: Check if renamed attribute is actually used, a referencer can be referencing other attributes from same BP, in which case closing asset editor is not required)\n * 3. Close any opened referencers in Editor\n * 4. Update CDO for any referencers to update property from Old Attribute property to the new one\n * 5. Reopen any closed editor previously, if any\n */" },
		{ "IncludePath", "Subsystems/GBAEditorSubsystem.h" },
		{ "ModuleRelativePath", "Public/Subsystems/GBAEditorSubsystem.h" },
		{ "ToolTip", "Editor subsystem to handle Gameplay Attribute property renames in Blueprint.\n\nChanging a variable name needs to be handled to prevent crash from happening if any Gameplay Effects is using it, and if\nthat Gameplay Effect was previously opened and focused again in editor (not relevant anymore since rework into using TWeakFieldPtr<FProperty>).\n\nThe Details customization for the Attribute or Effect using those needs to be updated \"live\", whereas in the usual case\nof having Attributes defined in cpp, code needs to be recompiled and editor restarted.\n\nWith Blueprints, we need a way to rename attributes and have Gameplay Effects (or other K2 nodes using Gameplay Attribute) updated\nto reference the new property.\n\n---\n\nSubsystem register to an OnVariableRename delegate fired off from `UGBAAttributeSetBlueprint`, and handle any editor specific code.\n\nWhen a rename happens, this event fires off and triggers the following logic in this subsystem:\n\n1. Get all referencers to the original Attribute Set Blueprints (its package name)\n2. Check if any referencers is currently opened in Editor, store them\n(TODO: Check if renamed attribute is actually used, a referencer can be referencing other attributes from same BP, in which case closing asset editor is not required)\n3. Close any opened referencers in Editor\n4. Update CDO for any referencers to update property from Old Attribute property to the new one\n5. Reopen any closed editor previously, if any" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBAEditorSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGBAEditorSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEditorSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributesEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAEditorSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBAEditorSubsystem_Statics::ClassParams = {
	&UGBAEditorSubsystem::StaticClass,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAEditorSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBAEditorSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBAEditorSubsystem()
{
	if (!Z_Registration_Info_UClass_UGBAEditorSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBAEditorSubsystem.OuterSingleton, Z_Construct_UClass_UGBAEditorSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBAEditorSubsystem.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTESEDITOR_API UClass* StaticClass<UGBAEditorSubsystem>()
{
	return UGBAEditorSubsystem::StaticClass();
}
UGBAEditorSubsystem::UGBAEditorSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBAEditorSubsystem);
UGBAEditorSubsystem::~UGBAEditorSubsystem() {}
// End Class UGBAEditorSubsystem

// Begin Registration
struct Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_Subsystems_GBAEditorSubsystem_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBAEditorSubsystem, UGBAEditorSubsystem::StaticClass, TEXT("UGBAEditorSubsystem"), &Z_Registration_Info_UClass_UGBAEditorSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBAEditorSubsystem), 919860060U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_Subsystems_GBAEditorSubsystem_h_1024343453(TEXT("/Script/BlueprintAttributesEditor"),
	Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_Subsystems_GBAEditorSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_Subsystems_GBAEditorSubsystem_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
