// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueprintAttributesScaffold/Public/GBAScaffoldPreviewSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGBAScaffoldPreviewSettings() {}

// Begin Cross Module References
BLUEPRINTATTRIBUTESSCAFFOLD_API UClass* Z_Construct_UClass_UGBAScaffoldPreviewSettings();
BLUEPRINTATTRIBUTESSCAFFOLD_API UClass* Z_Construct_UClass_UGBAScaffoldPreviewSettings_NoRegister();
BLUEPRINTATTRIBUTESSCAFFOLD_API UEnum* Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod();
BLUEPRINTATTRIBUTESSCAFFOLD_API UScriptStruct* Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
UPackage* Z_Construct_UPackage__Script_BlueprintAttributesScaffold();
// End Cross Module References

// Begin Enum EGBAPreviewSortMethod
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGBAPreviewSortMethod;
static UEnum* EGBAPreviewSortMethod_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EGBAPreviewSortMethod.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EGBAPreviewSortMethod.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod, (UObject*)Z_Construct_UPackage__Script_BlueprintAttributesScaffold(), TEXT("EGBAPreviewSortMethod"));
	}
	return Z_Registration_Info_UEnum_EGBAPreviewSortMethod.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTESSCAFFOLD_API UEnum* StaticEnum<EGBAPreviewSortMethod>()
{
	return EGBAPreviewSortMethod_StaticEnum();
}
struct Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
		{ "None.Comment", "// Properties will stay in the same order they were in the Blueprint class.\n" },
		{ "None.Name", "EGBAPreviewSortMethod::None" },
		{ "None.ToolTip", "Properties will stay in the same order they were in the Blueprint class." },
		{ "SortByAccessSpecifier.Comment", "// Properties will be grouped together by Access Specifiers, in order of visibility (public, protected, private).\n" },
		{ "SortByAccessSpecifier.Name", "EGBAPreviewSortMethod::SortByAccessSpecifier" },
		{ "SortByAccessSpecifier.ToolTip", "Properties will be grouped together by Access Specifiers, in order of visibility (public, protected, private)." },
		{ "SortForOptimalPadding.Comment", "// Properties will be sorted to minimize padding in compiled class layout.\n" },
		{ "SortForOptimalPadding.Name", "EGBAPreviewSortMethod::SortForOptimalPadding" },
		{ "SortForOptimalPadding.ToolTip", "Properties will be sorted to minimize padding in compiled class layout." },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGBAPreviewSortMethod::None", (int64)EGBAPreviewSortMethod::None },
		{ "EGBAPreviewSortMethod::SortByAccessSpecifier", (int64)EGBAPreviewSortMethod::SortByAccessSpecifier },
		{ "EGBAPreviewSortMethod::SortForOptimalPadding", (int64)EGBAPreviewSortMethod::SortForOptimalPadding },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_BlueprintAttributesScaffold,
	nullptr,
	"EGBAPreviewSortMethod",
	"EGBAPreviewSortMethod",
	Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod_Statics::Enum_MetaDataParams), Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod()
{
	if (!Z_Registration_Info_UEnum_EGBAPreviewSortMethod.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGBAPreviewSortMethod.InnerSingleton, Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EGBAPreviewSortMethod.InnerSingleton;
}
// End Enum EGBAPreviewSortMethod

// Begin ScriptStruct FGBAPreviewSyntaxColors
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GBAPreviewSyntaxColors;
class UScriptStruct* FGBAPreviewSyntaxColors::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GBAPreviewSyntaxColors.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GBAPreviewSyntaxColors.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors, (UObject*)Z_Construct_UPackage__Script_BlueprintAttributesScaffold(), TEXT("GBAPreviewSyntaxColors"));
	}
	return Z_Registration_Info_UScriptStruct_GBAPreviewSyntaxColors.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTESSCAFFOLD_API UScriptStruct* StaticStruct<FGBAPreviewSyntaxColors>()
{
	return FGBAPreviewSyntaxColors::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Comment_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Error_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Macro_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Typename_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Identifier_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Keyword_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_String_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Numeric_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Comment;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Error;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Macro;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Typename;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Identifier;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Keyword;
	static const UECodeGen_Private::FStructPropertyParams NewProp_String;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Numeric;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGBAPreviewSyntaxColors>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Comment = { "Comment", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAPreviewSyntaxColors, Comment), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Comment_MetaData), NewProp_Comment_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Error = { "Error", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAPreviewSyntaxColors, Error), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Error_MetaData), NewProp_Error_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Macro = { "Macro", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAPreviewSyntaxColors, Macro), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Macro_MetaData), NewProp_Macro_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Typename = { "Typename", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAPreviewSyntaxColors, Typename), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Typename_MetaData), NewProp_Typename_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Identifier = { "Identifier", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAPreviewSyntaxColors, Identifier), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Identifier_MetaData), NewProp_Identifier_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Keyword = { "Keyword", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAPreviewSyntaxColors, Keyword), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Keyword_MetaData), NewProp_Keyword_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_String = { "String", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAPreviewSyntaxColors, String), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_String_MetaData), NewProp_String_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Numeric = { "Numeric", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGBAPreviewSyntaxColors, Numeric), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Numeric_MetaData), NewProp_Numeric_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Comment,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Error,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Macro,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Typename,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Identifier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Keyword,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_String,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewProp_Numeric,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributesScaffold,
	nullptr,
	&NewStructOps,
	"GBAPreviewSyntaxColors",
	Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::PropPointers),
	sizeof(FGBAPreviewSyntaxColors),
	alignof(FGBAPreviewSyntaxColors),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors()
{
	if (!Z_Registration_Info_UScriptStruct_GBAPreviewSyntaxColors.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GBAPreviewSyntaxColors.InnerSingleton, Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GBAPreviewSyntaxColors.InnerSingleton;
}
// End ScriptStruct FGBAPreviewSyntaxColors

// Begin Class UGBAScaffoldPreviewSettings
void UGBAScaffoldPreviewSettings::StaticRegisterNativesUGBAScaffoldPreviewSettings()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGBAScaffoldPreviewSettings);
UClass* Z_Construct_UClass_UGBAScaffoldPreviewSettings_NoRegister()
{
	return UGBAScaffoldPreviewSettings::StaticClass();
}
struct Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/** Settings for the Blueprint Header View Plugin */" },
		{ "IncludePath", "GBAScaffoldPreviewSettings.h" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
		{ "ToolTip", "Settings for the Blueprint Header View Plugin" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SyntaxColors_MetaData[] = {
		{ "Category", "Settings|Style" },
		{ "Comment", "/** Syntax Highlighting colors for Blueprint Header View output */" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
		{ "ToolTip", "Syntax Highlighting colors for Blueprint Header View output" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectionColor_MetaData[] = {
		{ "Category", "Settings|Style" },
		{ "Comment", "/** Highlight color for selected items in the Blueprint Header View output */" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
		{ "ToolTip", "Highlight color for selected items in the Blueprint Header View output" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FontSize_MetaData[] = {
		{ "Category", "Settings|Style" },
		{ "ClampMax", "72" },
		{ "ClampMin", "6" },
		{ "Comment", "/** Font Size for the Blueprint Header View output */" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
		{ "ToolTip", "Font Size for the Blueprint Header View output" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SortMethod_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/** Sorting Method for Header View Functions and Properties */" },
		{ "ModuleRelativePath", "Public/GBAScaffoldPreviewSettings.h" },
		{ "ToolTip", "Sorting Method for Header View Functions and Properties" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_SyntaxColors;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SelectionColor;
	static const UECodeGen_Private::FIntPropertyParams NewProp_FontSize;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SortMethod_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SortMethod;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGBAScaffoldPreviewSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_SyntaxColors = { "SyntaxColors", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBAScaffoldPreviewSettings, SyntaxColors), Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SyntaxColors_MetaData), NewProp_SyntaxColors_MetaData) }; // 655526504
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_SelectionColor = { "SelectionColor", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBAScaffoldPreviewSettings, SelectionColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectionColor_MetaData), NewProp_SelectionColor_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_FontSize = { "FontSize", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBAScaffoldPreviewSettings, FontSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FontSize_MetaData), NewProp_FontSize_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_SortMethod_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_SortMethod = { "SortMethod", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGBAScaffoldPreviewSettings, SortMethod), Z_Construct_UEnum_BlueprintAttributesScaffold_EGBAPreviewSortMethod, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SortMethod_MetaData), NewProp_SortMethod_MetaData) }; // 2823728081
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_SyntaxColors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_SelectionColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_FontSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_SortMethod_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::NewProp_SortMethod,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_BlueprintAttributesScaffold,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::ClassParams = {
	&UGBAScaffoldPreviewSettings::StaticClass,
	"EditorPerProjectUserSettings",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::PropPointers),
	0,
	0x000000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGBAScaffoldPreviewSettings()
{
	if (!Z_Registration_Info_UClass_UGBAScaffoldPreviewSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGBAScaffoldPreviewSettings.OuterSingleton, Z_Construct_UClass_UGBAScaffoldPreviewSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGBAScaffoldPreviewSettings.OuterSingleton;
}
template<> BLUEPRINTATTRIBUTESSCAFFOLD_API UClass* StaticClass<UGBAScaffoldPreviewSettings>()
{
	return UGBAScaffoldPreviewSettings::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGBAScaffoldPreviewSettings);
UGBAScaffoldPreviewSettings::~UGBAScaffoldPreviewSettings() {}
// End Class UGBAScaffoldPreviewSettings

// Begin Registration
struct Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EGBAPreviewSortMethod_StaticEnum, TEXT("EGBAPreviewSortMethod"), &Z_Registration_Info_UEnum_EGBAPreviewSortMethod, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2823728081U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FGBAPreviewSyntaxColors::StaticStruct, Z_Construct_UScriptStruct_FGBAPreviewSyntaxColors_Statics::NewStructOps, TEXT("GBAPreviewSyntaxColors"), &Z_Registration_Info_UScriptStruct_GBAPreviewSyntaxColors, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGBAPreviewSyntaxColors), 655526504U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGBAScaffoldPreviewSettings, UGBAScaffoldPreviewSettings::StaticClass, TEXT("UGBAScaffoldPreviewSettings"), &Z_Registration_Info_UClass_UGBAScaffoldPreviewSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGBAScaffoldPreviewSettings), 1302168382U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_2113209153(TEXT("/Script/BlueprintAttributesScaffold"),
	Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Marketplace_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_BlueprintAttributes_Source_BlueprintAttributesScaffold_Public_GBAScaffoldPreviewSettings_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
