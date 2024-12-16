// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributesEditor/Public/GBAEditorSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBAEditorSettings() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTESEDITOR_API UClass* Z_Construct_UClass_UGBAEditorSettings();
BLUEPRINTATTRIBUTESEDITOR_API UClass* Z_Construct_UClass_UGBAEditorSettings_NoRegister();
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributesEditor();
// End Cross Module References

// Begin Class UGBAEditorSettings
void UGBAEditorSettings::StaticRegisterNativesUGBAEditorSettings()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBAEditorSettings);
UClass* Z_Construct_UClass_UGBAEditorSettings_NoRegister()
{
	return UGBAEditorSettings::StaticClass();
}
struct Z_Construct_UClass_UGBAEditorSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Common Settings for Blueprint Attributes plugin\n */" },
		{ "IncludePath", "GBAEditorSettings.h" },
		{ "ModuleRelativePath", "Public/GBAEditorSettings.h" },
		{ "ToolTip", "Common Settings for Blueprint Attributes plugin" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FilterAttributesList_MetaData[] = {
		{ "Category", "Details Customizations | Attributes" },
		{ "Comment", "/**\n\x09 * Set of gameplay attributes to ignore in attributes picker widget.\n\x09 *\n\x09 * Allows you to filter out a list of gameplay attributes from Attribute Sets in Gameplay Effects Blueprint\n\x09 * or any Blueprint nodes listing them (such as GetFloatAttribute())\n\x09 *\n\x09 * It can be useful if your project is never using pre-defined Attributes (such as AbilitySystemComponent.OutgoingDuration / IncomingDuration),\n\x09 * or plugins (such as GAS Companion GSCAttributeSet)\n\x09 *\n\x09 * This is a StartsWith search pattern, meaning any value here should be the beginning of an attribute (or set) we'd like to ignore, example:\n\x09 *\n\x09 * - AbilitySystemComponent\n\x09 * - AbilitySystemComponent.OutgoingDuration\n\x09 * - AbilitySystemComponent.IncomingDuration\n\x09 * - GSCAttributeSet\n\x09 * - GSCAttributeSet.Mana\n\x09 */" },
		{ "DisplayName", "Filter Out Attributes in Details View" },
		{ "ModuleRelativePath", "Public/GBAEditorSettings.h" },
		{ "ToolTip", "Set of gameplay attributes to ignore in attributes picker widget.\n\nAllows you to filter out a list of gameplay attributes from Attribute Sets in Gameplay Effects Blueprint\nor any Blueprint nodes listing them (such as GetFloatAttribute())\n\nIt can be useful if your project is never using pre-defined Attributes (such as AbilitySystemComponent.OutgoingDuration / IncomingDuration),\nor plugins (such as GAS Companion GSCAttributeSet)\n\nThis is a StartsWith search pattern, meaning any value here should be the beginning of an attribute (or set) we'd like to ignore, example:\n\n- AbilitySystemComponent\n- AbilitySystemComponent.OutgoingDuration\n- AbilitySystemComponent.IncomingDuration\n- GSCAttributeSet\n- GSCAttributeSet.Mana" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseCompactView_MetaData[] = {
		{ "Category", "Details Customizations | Attribute Data Properties" },
		{ "Comment", "/**\n\x09 * Whether to use a compact view mode for Gameplay Attribute Data properties in Attribute Set Blueprints.\n\x09 *\n\x09 * For both class defaults variables and when viewing / editing a single Attribute Data property, making the edition of\n\x09 * BaseValue possible in the header of the row.\n\x09 *\n\x09 * Only for simple Gameplay Attribute Data properties, clamped properties still display using the full extended version.\n\x09 */" },
		{ "ModuleRelativePath", "Public/GBAEditorSettings.h" },
		{ "ToolTip", "Whether to use a compact view mode for Gameplay Attribute Data properties in Attribute Set Blueprints.\n\nFor both class defaults variables and when viewing / editing a single Attribute Data property, making the edition of\nBaseValue possible in the header of the row.\n\nOnly for simple Gameplay Attribute Data properties, clamped properties still display using the full extended version." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeaderFormatText_MetaData[] = {
		{ "Category", "Details Customizations | Attribute Data Properties" },
		{ "Comment", "/**\n\x09 * Customize how the header row is displayed and what should be included.\n\x09 *\n\x09 * This is a FText::Format format string, with two floats being passed in as an argument (BaseValue and CurrentValue). Both float\n\x09 * values are converted to String with \"%.2f\" to reduce precision to only two decimals.\n\x09 *\n\x09 * Default Value: \"Base: {0}, Current: {1}\"\n\x09 */" },
		{ "EditCondition", "!bUseCompactView" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/GBAEditorSettings.h" },
		{ "ToolTip", "Customize how the header row is displayed and what should be included.\n\nThis is a FText::Format format string, with two floats being passed in as an argument (BaseValue and CurrentValue). Both float\nvalues are converted to String with \"%.2f\" to reduce precision to only two decimals.\n\nDefault Value: \"Base: {0}, Current: {1}\"" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDisplayCurrentValue_MetaData[] = {
		{ "Category", "Details Customizations | Attribute Data Properties" },
		{ "Comment", "/**\n\x09 * Whether to display Attributes' CurrentValue property as well, as a BlueprintReadOnly property (not editable).\n\x09 *\n\x09 * CurrentValue is kept in sync with BaseValue when edited within the details panel.\n\x09 */" },
		{ "EditCondition", "!bUseCompactView" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/GBAEditorSettings.h" },
		{ "ToolTip", "Whether to display Attributes' CurrentValue property as well, as a BlueprintReadOnly property (not editable).\n\nCurrentValue is kept in sync with BaseValue when edited within the details panel." },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_FilterAttributesList_ElementProp;
	static const UECodeGen_Private::FSetPropertyParams NewProp_FilterAttributesList;
	static void NewProp_bUseCompactView_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseCompactView;
	static const UECodeGen_Private::FTextPropertyParams NewProp_HeaderFormatText;
	static void NewProp_bDisplayCurrentValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDisplayCurrentValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBAEditorSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_FilterAttributesList_ElementProp = { "FilterAttributesList", nullptr, (EPropertyFlags)0x0000000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_FilterAttributesList = { "FilterAttributesList", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBAEditorSettings, FilterAttributesList), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FilterAttributesList_MetaData), NewProp_FilterAttributesList_MetaData) };
void Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_bUseCompactView_SetBit(void* Obj)
{
	((UGBAEditorSettings*)Obj)->bUseCompactView = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_bUseCompactView = { "bUseCompactView", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGBAEditorSettings), &Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_bUseCompactView_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseCompactView_MetaData), NewProp_bUseCompactView_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_HeaderFormatText = { "HeaderFormatText", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBAEditorSettings, HeaderFormatText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeaderFormatText_MetaData), NewProp_HeaderFormatText_MetaData) };
void Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_bDisplayCurrentValue_SetBit(void* Obj)
{
	((UGBAEditorSettings*)Obj)->bDisplayCurrentValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_bDisplayCurrentValue = { "bDisplayCurrentValue", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGBAEditorSettings), &Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_bDisplayCurrentValue_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDisplayCurrentValue_MetaData), NewProp_bDisplayCurrentValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGBAEditorSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_FilterAttributesList_ElementProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_FilterAttributesList,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_bUseCompactView,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_HeaderFormatText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAEditorSettings_Statics::NewProp_bDisplayCurrentValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAEditorSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGBAEditorSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributesEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAEditorSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBAEditorSettings_Statics::ClassParams = {
	&UGBAEditorSettings::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGBAEditorSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGBAEditorSettings_Statics::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAEditorSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBAEditorSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBAEditorSettings()
{
	if (!Z_Registration_Info_UClass_UGBAEditorSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBAEditorSettings.OuterSingleton, Z_Construct_UClass_UGBAEditorSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBAEditorSettings.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTESEDITOR_API UClass* StaticClass<UGBAEditorSettings>()
{
	return UGBAEditorSettings::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBAEditorSettings);
UGBAEditorSettings::~UGBAEditorSettings() {}
// End Class UGBAEditorSettings

// Begin Registration
struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_GBAEditorSettings_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBAEditorSettings, UGBAEditorSettings::StaticClass, TEXT("UGBAEditorSettings"), &Z_Registration_Info_UClass_UGBAEditorSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBAEditorSettings), 971968209U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_GBAEditorSettings_h_934610045(TEXT("/Script/BlueprintAttributesEditor"),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_GBAEditorSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesEditor_Public_GBAEditorSettings_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
