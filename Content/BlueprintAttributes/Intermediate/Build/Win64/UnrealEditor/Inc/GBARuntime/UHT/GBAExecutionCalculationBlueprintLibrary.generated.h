// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Utils/GBAExecutionCalculationBlueprintLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGameplayAttribute;
struct FGameplayEffectAttributeCaptureDefinition;
struct FGameplayEffectContextHandle;
struct FGameplayEffectCustomExecutionOutput;
struct FGameplayEffectCustomExecutionParameters;
struct FGameplayEffectSpec;
struct FGameplayTagContainer;
#ifdef BLUEPRINTATTRIBUTES_GBAExecutionCalculationBlueprintLibrary_generated_h
#error "GBAExecutionCalculationBlueprintLibrary.generated.h already included, missing '#pragma once' in GBAExecutionCalculationBlueprintLibrary.h"
#endif
#define BLUEPRINTATTRIBUTES_GBAExecutionCalculationBlueprintLibrary_generated_h

#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execAddOutputModifier); \
	DECLARE_FUNCTION(execAttemptCalculateCapturedAttributeMagnitudeWithBase); \
	DECLARE_FUNCTION(execAttemptCalculateCapturedAttributeMagnitude); \
	DECLARE_FUNCTION(execGetTargetTags); \
	DECLARE_FUNCTION(execGetSourceTags); \
	DECLARE_FUNCTION(execGetEffectContext); \
	DECLARE_FUNCTION(execGetOwningSpec);


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGBAExecutionCalculationBlueprintLibrary(); \
	friend struct Z_Construct_UClass_UGBAExecutionCalculationBlueprintLibrary_Statics; \
public: \
	DECLARE_CLASS(UGBAExecutionCalculationBlueprintLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/BlueprintAttributes"), NO_API) \
	DECLARE_SERIALIZER(UGBAExecutionCalculationBlueprintLibrary)


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_26_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGBAExecutionCalculationBlueprintLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UGBAExecutionCalculationBlueprintLibrary(UGBAExecutionCalculationBlueprintLibrary&&); \
	UGBAExecutionCalculationBlueprintLibrary(const UGBAExecutionCalculationBlueprintLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGBAExecutionCalculationBlueprintLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGBAExecutionCalculationBlueprintLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGBAExecutionCalculationBlueprintLibrary) \
	NO_API virtual ~UGBAExecutionCalculationBlueprintLibrary();


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_23_PROLOG
#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_26_INCLASS_NO_PURE_DECLS \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BLUEPRINTATTRIBUTES_API UClass* StaticClass<class UGBAExecutionCalculationBlueprintLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBAExecutionCalculationBlueprintLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
