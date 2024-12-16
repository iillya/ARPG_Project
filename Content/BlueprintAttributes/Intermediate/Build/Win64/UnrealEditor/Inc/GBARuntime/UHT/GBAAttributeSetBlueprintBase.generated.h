// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Abilities/GBAAttributeSetBlueprintBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UAbilitySystemComponent;
struct FGameplayAbilityActorInfo;
struct FGameplayAttribute;
struct FGameplayAttributeData;
struct FGBAAttributeSetExecutionData;
struct FGBAGameplayClampedAttributeData;
#ifdef BLUEPRINTATTRIBUTES_GBAAttributeSetBlueprintBase_generated_h
#error "GBAAttributeSetBlueprintBase.generated.h already included, missing '#pragma once' in GBAAttributeSetBlueprintBase.h"
#endif
#define BLUEPRINTATTRIBUTES_GBAAttributeSetBlueprintBase_generated_h

#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_28_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGBAAttributeSetExecutionData_Statics; \
	static class UScriptStruct* StaticStruct();


template<> BLUEPRINTATTRIBUTES_API UScriptStruct* StaticStruct<struct FGBAAttributeSetExecutionData>();

#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_109_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGBAClampDefinition_Statics; \
	static class UScriptStruct* StaticStruct();


template<> BLUEPRINTATTRIBUTES_API UScriptStruct* StaticStruct<struct FGBAClampDefinition>();

#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_161_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGBAGameplayClampedAttributeData_Statics; \
	static class UScriptStruct* StaticStruct(); \
	typedef FGameplayAttributeData Super;


template<> BLUEPRINTATTRIBUTES_API UScriptStruct* StaticStruct<struct FGBAGameplayClampedAttributeData>();

#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual bool K2_PreGameplayEffectExecute_Implementation(FGameplayAttribute const& InAttribute, FGBAAttributeSetExecutionData const& InData); \
	DECLARE_FUNCTION(execHandleRepNotifyForGameplayClampedAttributeData); \
	DECLARE_FUNCTION(execHandleRepNotifyForGameplayAttributeData); \
	DECLARE_FUNCTION(execK2_GetActorInfo); \
	DECLARE_FUNCTION(execK2_GetOwningAbilitySystemComponent); \
	DECLARE_FUNCTION(execK2_GetOwningActor); \
	DECLARE_FUNCTION(execK2_SetAttributeValue); \
	DECLARE_FUNCTION(execK2_GetAttributeBaseValue); \
	DECLARE_FUNCTION(execK2_GetAttributeValue); \
	DECLARE_FUNCTION(execClampAttributeValue); \
	DECLARE_FUNCTION(execK2_PreGameplayEffectExecute);


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_CALLBACK_WRAPPERS
#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_ARCHIVESERIALIZER \
	DECLARE_FSTRUCTUREDARCHIVE_SERIALIZER(UGBAAttributeSetBlueprintBase, NO_API)


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGBAAttributeSetBlueprintBase(); \
	friend struct Z_Construct_UClass_UGBAAttributeSetBlueprintBase_Statics; \
public: \
	DECLARE_CLASS(UGBAAttributeSetBlueprintBase, UAttributeSet, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/BlueprintAttributes"), NO_API) \
	DECLARE_SERIALIZER(UGBAAttributeSetBlueprintBase) \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_ARCHIVESERIALIZER


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UGBAAttributeSetBlueprintBase(UGBAAttributeSetBlueprintBase&&); \
	UGBAAttributeSetBlueprintBase(const UGBAAttributeSetBlueprintBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGBAAttributeSetBlueprintBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGBAAttributeSetBlueprintBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGBAAttributeSetBlueprintBase) \
	NO_API virtual ~UGBAAttributeSetBlueprintBase();


#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_186_PROLOG
#define FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_CALLBACK_WRAPPERS \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_INCLASS_NO_PURE_DECLS \
	FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h_189_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BLUEPRINTATTRIBUTES_API UClass* StaticClass<class UGBAAttributeSetBlueprintBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Abilities_GBAAttributeSetBlueprintBase_h


#define FOREACH_ENUM_EGBACLAMPINGTYPE(op) \
	op(EGBAClampingType::None) \
	op(EGBAClampingType::Float) \
	op(EGBAClampingType::AttributeBased) 

enum class EGBAClampingType : uint8;
template<> struct TIsUEnumClass<EGBAClampingType> { enum { Value = true }; };
template<> BLUEPRINTATTRIBUTES_API UEnum* StaticEnum<EGBAClampingType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
