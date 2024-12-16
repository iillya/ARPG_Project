// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributes/Public/Utils/GBASerializationBlueprintLibrary.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBASerializationBlueprintLibrary() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBASaveGame();
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBASaveGame_NoRegister();
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBASerializationBlueprintLibrary();
BLUEPRINTATTRIBUTES_API UClass* Z_Construct_UClass_UGBASerializationBlueprintLibrary_NoRegister();
BLUEPRINTATTRIBUTES_API UScriptStruct* Z_Construct_UScriptStruct_FGBAActorSaveData();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
ENGINE_API UClass* Z_Construct_UClass_USaveGame();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributes();
// End Cross Module References

// Begin ScriptStruct FGBAActorSaveData
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GBAActorSaveData;
class UScriptStruct* FGBAActorSaveData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GBAActorSaveData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GBAActorSaveData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGBAActorSaveData, (UObject*)Z_Construct_UPackage__Script_BlueprintAttributes(), TEXT("GBAActorSaveData"));
	}
	return Z_Registration_Info_UScriptStruct_GBAActorSaveData.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UScriptStruct* StaticStruct<FGBAActorSaveData>()
{
	return FGBAActorSaveData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGBAActorSaveData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorName_MetaData[] = {
		{ "Category", "Save" },
		{ "Comment", "/* Identifier for which Actor this belongs to */" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
		{ "ToolTip", "Identifier for which Actor this belongs to" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Transform_MetaData[] = {
		{ "Category", "Save" },
		{ "Comment", "/* For movable Actors, keep location,rotation,scale. */" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
		{ "ToolTip", "For movable Actors, keep location,rotation,scale." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ByteData_MetaData[] = {
		{ "Category", "Save" },
		{ "Comment", "/* Contains all 'SaveGame' marked variables of the Actor */" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
		{ "ToolTip", "Contains all 'SaveGame' marked variables of the Actor" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_ActorName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Transform;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ByteData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ByteData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGBAActorSaveData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewProp_ActorName = { "ActorName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAActorSaveData, ActorName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorName_MetaData), NewProp_ActorName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewProp_Transform = { "Transform", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAActorSaveData, Transform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Transform_MetaData), NewProp_Transform_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewProp_ByteData_Inner = { "ByteData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewProp_ByteData = { "ByteData", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAActorSaveData, ByteData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ByteData_MetaData), NewProp_ByteData_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewProp_ActorName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewProp_Transform,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewProp_ByteData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewProp_ByteData,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
	nullptr,
	&NewStructOps,
	"GBAActorSaveData",
	Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::PropPointers),
	sizeof(FGBAActorSaveData),
	alignof(FGBAActorSaveData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGBAActorSaveData()
{
	if (!Z_Registration_Info_UScriptStruct_GBAActorSaveData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GBAActorSaveData.InnerSingleton, Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GBAActorSaveData.InnerSingleton;
}
// End ScriptStruct FGBAActorSaveData

// Begin Class UGBASaveGame
void UGBASaveGame::StaticRegisterNativesUGBASaveGame()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBASaveGame);
UClass* Z_Construct_UClass_UGBASaveGame_NoRegister()
{
	return UGBASaveGame::StaticClass();
}
struct Z_Construct_UClass_UGBASaveGame_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Utils/GBASerializationBlueprintLibrary.h" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SaveGameName_MetaData[] = {
		{ "Category", "Save" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SavedActor_MetaData[] = {
		{ "Category", "Save" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SaveGameName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SavedActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBASaveGame>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGBASaveGame_Statics::NewProp_SaveGameName = { "SaveGameName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBASaveGame, SaveGameName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SaveGameName_MetaData), NewProp_SaveGameName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGBASaveGame_Statics::NewProp_SavedActor = { "SavedActor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBASaveGame, SavedActor), Z_Construct_UScriptStruct_FGBAActorSaveData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SavedActor_MetaData), NewProp_SavedActor_MetaData) }; // 2215854928
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGBASaveGame_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBASaveGame_Statics::NewProp_SaveGameName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBASaveGame_Statics::NewProp_SavedActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBASaveGame_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGBASaveGame_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USaveGame,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBASaveGame_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBASaveGame_Statics::ClassParams = {
	&UGBASaveGame::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGBASaveGame_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGBASaveGame_Statics::PropPointers),
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBASaveGame_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBASaveGame_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBASaveGame()
{
	if (!Z_Registration_Info_UClass_UGBASaveGame.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBASaveGame.OuterSingleton, Z_Construct_UClass_UGBASaveGame_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBASaveGame.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UClass* StaticClass<UGBASaveGame>()
{
	return UGBASaveGame::StaticClass();
}
UGBASaveGame::UGBASaveGame(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBASaveGame);
UGBASaveGame::~UGBASaveGame() {}
// End Class UGBASaveGame

// Begin Class UGBASerializationBlueprintLibrary Function SerializeAbilitySystemComponent
struct Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics
{
	struct GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms
	{
		UAbilitySystemComponent* InASC;
		TArray<uint8> InData;
		bool bIsSaving;
		bool bIsASCImplementingSerialize;
		TArray<uint8> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Blueprint Attributes | Serialize" },
		{ "Comment", "/**\n\x09 * Helper method to serialize an actor's Ability System Component and all of its SaveGame marked FGameplayAttributes.\n\x09 * \n\x09 * If saving, will write FGameplayAttribute values\n\x09 * \n\x09 * ```cpp\n\x09 * void UMyAttributeSet::Serialize(FArchive& Ar)\n\x09 * {\n\x09 * \x09Super::Serialize(Ar);\n\x09 *\n\x09 * \x09if (Ar.IsSaveGame())\n\x09 * \x09{\n\x09 * \x09\x09""FGBAUtils::SerializeAttributeSet(this, Ar);\n\x09 * \x09}\n\x09 * }\n\x09 * ```\n\x09 *\n\x09 * TODO: It should ideally use a structured archive and store values along the field path (as a map or an array with\n\x09 * attribute set owner / attribute name)\n\x09 * \n\x09 * @param InASC Ability System Component from which to serialize the AttributeSets\n\x09 * @param InData The binary data to serialize from and to as an array of bytes\n\x09 * @param bIsSaving Determines if the serialization should read or write from the underlying archive\n\x09 * (This should be true when saving, and false when loading)\n\x09 * @param bIsASCImplementingSerialize Whether the ASC component that is passed in is implementing Serialize(),\n\x09 * and whether we should use it.\n\x09 *\x09\x09\x09\x09\x09\n\x09 * @returns The input Binary Data modified along the way in case of saving\n\x09 */" },
		{ "CPP_Default_bIsASCImplementingSerialize", "false" },
		{ "CPP_Default_bIsSaving", "true" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
		{ "ToolTip", "Helper method to serialize an actor's Ability System Component and all of its SaveGame marked FGameplayAttributes.\n\nIf saving, will write FGameplayAttribute values\n\n```cpp\nvoid UMyAttributeSet::Serialize(FArchive& Ar)\n{\n     Super::Serialize(Ar);\n\n     if (Ar.IsSaveGame())\n     {\n             FGBAUtils::SerializeAttributeSet(this, Ar);\n     }\n}\n```\n\nTODO: It should ideally use a structured archive and store values along the field path (as a map or an array with\nattribute set owner / attribute name)\n\n@param InASC Ability System Component from which to serialize the AttributeSets\n@param InData The binary data to serialize from and to as an array of bytes\n@param bIsSaving Determines if the serialization should read or write from the underlying archive\n(This should be true when saving, and false when loading)\n@param bIsASCImplementingSerialize Whether the ASC component that is passed in is implementing Serialize(),\nand whether we should use it.\n\n@returns The input Binary Data modified along the way in case of saving" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InASC_MetaData[] = {
		{ "DisplayName", "AbilitySystemComponent" },
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InData_MetaData[] = {
		{ "DisplayName", "Data" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsSaving_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsASCImplementingSerialize_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InASC;
	static const UECodeGen_Private::FBytePropertyParams NewProp_InData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InData;
	static void NewProp_bIsSaving_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsSaving;
	static void NewProp_bIsASCImplementingSerialize_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsASCImplementingSerialize;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_InASC = { "InASC", nullptr, (EPropertyFlags)0x0010000008080180, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms, InASC), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InASC_MetaData), NewProp_InASC_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_InData_Inner = { "InData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_InData = { "InData", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms, InData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InData_MetaData), NewProp_InData_MetaData) };
void Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_bIsSaving_SetBit(void* Obj)
{
	((GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms*)Obj)->bIsSaving = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_bIsSaving = { "bIsSaving", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms), &Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_bIsSaving_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsSaving_MetaData), NewProp_bIsSaving_MetaData) };
void Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_bIsASCImplementingSerialize_SetBit(void* Obj)
{
	((GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms*)Obj)->bIsASCImplementingSerialize = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_bIsASCImplementingSerialize = { "bIsASCImplementingSerialize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms), &Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_bIsASCImplementingSerialize_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsASCImplementingSerialize_MetaData), NewProp_bIsASCImplementingSerialize_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_InASC,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_InData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_InData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_bIsSaving,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_bIsASCImplementingSerialize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGBASerializationBlueprintLibrary, nullptr, "SerializeAbilitySystemComponent", nullptr, nullptr, Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::GBASerializationBlueprintLibrary_eventSerializeAbilitySystemComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGBASerializationBlueprintLibrary::execSerializeAbilitySystemComponent)
{
	P_GET_OBJECT_REF(UAbilitySystemComponent,Z_Param_Out_InASC);
	P_GET_TARRAY_REF(uint8,Z_Param_Out_InData);
	P_GET_UBOOL(Z_Param_bIsSaving);
	P_GET_UBOOL(Z_Param_bIsASCImplementingSerialize);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<uint8>*)Z_Param__Result=UGBASerializationBlueprintLibrary::SerializeAbilitySystemComponent(Z_Param_Out_InASC,Z_Param_Out_InData,Z_Param_bIsSaving,Z_Param_bIsASCImplementingSerialize);
	P_NATIVE_END;
}
// End Class UGBASerializationBlueprintLibrary Function SerializeAbilitySystemComponent

// Begin Class UGBASerializationBlueprintLibrary
void UGBASerializationBlueprintLibrary::StaticRegisterNativesUGBASerializationBlueprintLibrary()
{
	UClass* Class = UGBASerializationBlueprintLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "SerializeAbilitySystemComponent", &UGBASerializationBlueprintLibrary::execSerializeAbilitySystemComponent },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBASerializationBlueprintLibrary);
UClass* Z_Construct_UClass_UGBASerializationBlueprintLibrary_NoRegister()
{
	return UGBASerializationBlueprintLibrary::StaticClass();
}
struct Z_Construct_UClass_UGBASerializationBlueprintLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Blueprint library for blueprint attribute sets.\n *\n * Includes serialization helpers, Save Game related.\n */" },
		{ "IncludePath", "Utils/GBASerializationBlueprintLibrary.h" },
		{ "ModuleRelativePath", "Public/Utils/GBASerializationBlueprintLibrary.h" },
		{ "ToolTip", "Blueprint library for blueprint attribute sets.\n\nIncludes serialization helpers, Save Game related." },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGBASerializationBlueprintLibrary_SerializeAbilitySystemComponent, "SerializeAbilitySystemComponent" }, // 4136857422
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBASerializationBlueprintLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UGBASerializationBlueprintLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBASerializationBlueprintLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBASerializationBlueprintLibrary_Statics::ClassParams = {
	&UGBASerializationBlueprintLibrary::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBASerializationBlueprintLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBASerializationBlueprintLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBASerializationBlueprintLibrary()
{
	if (!Z_Registration_Info_UClass_UGBASerializationBlueprintLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBASerializationBlueprintLibrary.OuterSingleton, Z_Construct_UClass_UGBASerializationBlueprintLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBASerializationBlueprintLibrary.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTES_API UClass* StaticClass<UGBASerializationBlueprintLibrary>()
{
	return UGBASerializationBlueprintLibrary::StaticClass();
}
UGBASerializationBlueprintLibrary::UGBASerializationBlueprintLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBASerializationBlueprintLibrary);
UGBASerializationBlueprintLibrary::~UGBASerializationBlueprintLibrary() {}
// End Class UGBASerializationBlueprintLibrary

// Begin Registration
struct Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBASerializationBlueprintLibrary_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FGBAActorSaveData::StaticStruct, Z_Construct_UScriptStruct_FGBAActorSaveData_Statics::NewStructOps, TEXT("GBAActorSaveData"), &Z_Registration_Info_UScriptStruct_GBAActorSaveData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGBAActorSaveData), 2215854928U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBASaveGame, UGBASaveGame::StaticClass, TEXT("UGBASaveGame"), &Z_Registration_Info_UClass_UGBASaveGame, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBASaveGame), 1755791503U) },
		{ Z_Construct_UClass_UGBASerializationBlueprintLibrary, UGBASerializationBlueprintLibrary::StaticClass, TEXT("UGBASerializationBlueprintLibrary"), &Z_Registration_Info_UClass_UGBASerializationBlueprintLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBASerializationBlueprintLibrary), 1722524405U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBASerializationBlueprintLibrary_h_1725439678(TEXT("/Script/BlueprintAttributes"),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBASerializationBlueprintLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBASerializationBlueprintLibrary_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBASerializationBlueprintLibrary_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Marketplace_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributes_Public_Utils_GBASerializationBlueprintLibrary_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
