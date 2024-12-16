// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GBAScaffoldPreviewSettings.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef BLUEPRINTATTRIBUTESSCAFFOLD_GBAScaffoldPreviewSettings_generated_h
#error "GBAScaffoldPreviewSettings.generated.h already included, missing '#pragma once' in GBAScaffoldPreviewSettings.h"
#endif
#define BLUEPRINTATTRIBUTESSCAFFOLD_GBAScaffoldPreviewSettings_generated_h

#define FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_24_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics; \
	BLUEPRINTATTRIBUTESSCAFFOLD_API static class UScriptStruct* StaticStruct();


template<> BLUEPRINTATTRIBUTESSCAFFOLD_API UScriptStruct* StaticStruct<struct FGBAPreviewSyntaxColors>();

#define FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_57_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGBAScaffoldPreviewSettings(); \
	friend struct Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics; \
public: \
	DECLARE_CLASS(UGBAScaffoldPreviewSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/BlueprintAttributesScaffold"), NO_API) \
	DECLARE_SERIALIZER(UGBAScaffoldPreviewSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("EditorPerProjectUserSettings");} \



#define FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_57_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UGBAScaffoldPreviewSettings(UGBAScaffoldPreviewSettings&&); \
	UGBAScaffoldPreviewSettings(const UGBAScaffoldPreviewSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGBAScaffoldPreviewSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGBAScaffoldPreviewSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGBAScaffoldPreviewSettings) \
	NO_API virtual ~UGBAScaffoldPreviewSettings();


#define FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_54_PROLOG
#define FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_57_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_57_INCLASS_NO_PURE_DECLS \
	FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_57_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BLUEPRINTATTRIBUTESSCAFFOLD_API UClass* StaticClass<class UGBAScaffoldPreviewSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h


#define FOREACH_ENUM_EGBAPREVIEWSORTMETHOD(op) \
	op(EGBAPreviewSortMethod::None) \
	op(EGBAPreviewSortMethod::SortByAccessSpecifier) \
	op(EGBAPreviewSortMethod::SortForOptimalPadding) 

enum class EGBAPreviewSortMethod : uint8;
template<> struct TIsUEnumClass<EGBAPreviewSortMethod> { enum { Value = true }; };
template<> BLUEPRINTATTRIBUTESSCAFFOLD_API UEnum* StaticEnum<EGBAPreviewSortMethod>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
