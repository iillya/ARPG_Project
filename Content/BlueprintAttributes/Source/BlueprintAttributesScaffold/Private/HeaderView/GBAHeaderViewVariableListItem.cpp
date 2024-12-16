// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAHeaderViewVariableListItem.h"
#include "EdGraphSchema_K2.h"
#include "EdMode.h"
#include "Engine/Blueprint.h"
#include "Engine/UserDefinedStruct.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/StructureEditorUtils.h"
#include "LineEndings/GBALineEndings.h"
#include "Misc/EngineVersionComparison.h"
#include "Models/GBAAttributeSetWizardViewModel.h"

#define LOCTEXT_NAMESPACE "FGBAHeaderViewVariableListItem"

FGBAHeaderViewVariableListItem::FGBAHeaderViewVariableListItem(const FProperty& InVarProperty, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	// Format comment
	{
		FString Comment = InVarProperty.GetMetaData(FBlueprintMetadata::MD_Tooltip);
		if (Comment.IsEmpty())
		{
			Comment = TEXT("Please add a variable description");
		}

		FormatCommentString(Comment, RawItemString, RichTextString);
	}

	// Add Delegate type declaration if needed
	// i.e. DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTypeName, ParamType, ParamName);
	if (const FMulticastDelegateProperty* AsDelegate = CastField<FMulticastDelegateProperty>(&InVarProperty))
	{
		FormatDelegateDeclaration(*AsDelegate);
	}

	// Add Deprecation message if present
	if (InVarProperty.HasAnyPropertyFlags(CPF_Deprecated))
	{
		FString DeprecationMessage = InVarProperty.GetMetaData(FBlueprintMetadata::MD_DeprecationMessage);
		if (DeprecationMessage.IsEmpty())
		{
			DeprecationMessage = TEXT("Please add a deprecation message.");
		}

		const FString EngineVersionString = FEngineVersion::Current().ToString(EVersionComponent::Patch);

		RawItemString += FString::Printf(TEXT("\nUE_DEPRECATED(%s, \"%s\")"), *EngineVersionString, *DeprecationMessage);
		RichTextString += FString::Printf(TEXT("\n<%s>UE_DEPRECATED</>(%s, \"%s\")"), *GBA::HeaderViewSyntaxDecorators::MacroDecorator, *EngineVersionString, *DeprecationMessage);
	}

	// Add the UPROPERTY specifiers
	// i.e. UPROPERTY(BlueprintReadWrite, Category="Variable Category")
	{
		const FString AdditionalSpecifiers = GetConditionalUPropertySpecifiers(InVarProperty);

		// Always add Blueprintable and BlueprintType
		RawItemString += FString::Printf(TEXT("\nUPROPERTY(%s)"), *AdditionalSpecifiers);
		RichTextString += FString::Printf(TEXT("\n<%s>UPROPERTY</>(%s)"), *GBA::HeaderViewSyntaxDecorators::MacroDecorator, *AdditionalSpecifiers);
	}

	// Add the variable declaration line
	// i.e. Type VariableName;
	{
		const FString Typename = GetCPPTypenameForProperty(&InVarProperty, /*bIsMemberProperty=*/true);
		const FString VarName = InVarProperty.GetAuthoredName();
		const bool bLegalName = IsValidCPPIdentifier(VarName);

		const FString* IdentifierDecorator = &GBA::HeaderViewSyntaxDecorators::IdentifierDecorator;
		if (!bLegalName)
		{
			IllegalName = FName(VarName);
			IdentifierDecorator = &GBA::HeaderViewSyntaxDecorators::ErrorDecorator;
		}

		UClass* OwnerClass = InVarProperty.GetOwnerClass();
		check(OwnerClass);
		const UClass* AuthoritativeClass = OwnerClass->GetAuthoritativeClass();
		check(AuthoritativeClass);
		
		const FString DesiredClassName = InViewModel->GetNewClassName();
		const FString PropertyValue = GetPropertyValue(InVarProperty, AuthoritativeClass->GetDefaultObject(false), DesiredClassName);
		const FString RichTextPropertyValue = GetPropertyValue(InVarProperty, AuthoritativeClass->GetDefaultObject(false), DesiredClassName, true);
		const FString OperatorString = PropertyValue.IsEmpty() ? TEXT("") : TEXT(" = ");
		RawItemString += FString::Printf(TEXT("\n%s %s%s%s;"), *Typename, *VarName, *OperatorString, *PropertyValue);
		RichTextString += FString::Printf(
			TEXT("\n<%s>%s</> <%s>%s</>%s%s;"),
			*GBA::HeaderViewSyntaxDecorators::TypenameDecorator,
			*Typename.Replace(TEXT("<"), TEXT("&lt;")).Replace(TEXT(">"), TEXT("&gt;")),
			**IdentifierDecorator,
			*VarName,
			*OperatorString,
			*RichTextPropertyValue
		);
	}

	// indent item
	RawItemString.InsertAt(0, TEXT("\t"));
	RichTextString.InsertAt(0, TEXT("\t"));
	RawItemString.ReplaceInline(TEXT("\n"), TEXT("\n\t"));
	RichTextString.ReplaceInline(TEXT("\n"), TEXT("\n\t"));

	// normalize to platform newlines
	GBA::String::ToHostLineEndingsInline(RawItemString);
	GBA::String::ToHostLineEndingsInline(RichTextString);
}

FGBAHeaderViewListItemPtr FGBAHeaderViewVariableListItem::Create(const FProperty& VarProperty, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	return MakeShareable(new FGBAHeaderViewVariableListItem(VarProperty, InViewModel));
}

void FGBAHeaderViewVariableListItem::ExtendContextMenu(FMenuBuilder& InMenuBuilder, const TWeakObjectPtr<UObject> InAsset)
{
	if (!IllegalName.IsNone())
	{
#if UE_VERSION_NEWER_THAN(5, 1, -1)
		InMenuBuilder.AddVerifiedEditableText(LOCTEXT("RenameItem", "Rename Variable"),
			LOCTEXT("RenameItemTooltip", "Renames this variable in the Blueprint\nThis variable name is not a legal C++ identifier."),
			FSlateIcon(),
			FText::FromName(IllegalName),
			FOnVerifyTextChanged::CreateSP(this, &FGBAHeaderViewVariableListItem::OnVerifyRenameTextChanged, InAsset),
			FOnTextCommitted::CreateSP(this, &FGBAHeaderViewVariableListItem::OnRenameTextCommitted, InAsset)
		);
#endif
	}
}

FBPVariableDescription* FGBAHeaderViewVariableListItem::GetBlueprintVariableDescription(const FName& InVarPropertyName, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	check(InViewModel.IsValid());
	
	FBPVariableDescription* VariableDesc = nullptr;
	if (UBlueprint* Blueprint = InViewModel->GetSelectedBlueprint().Get())
	{
		VariableDesc = Blueprint->NewVariables.FindByPredicate([InVarPropertyName](const FBPVariableDescription& Desc)
		{
			return Desc.VarName == InVarPropertyName;
		});
	}
	
	return VariableDesc;
}

void FGBAHeaderViewVariableListItem::FormatDelegateDeclaration(const FMulticastDelegateProperty& DelegateProp)
{
	if (const UFunction* SigFunction = DelegateProp.SignatureFunction)
	{
		static const TMap<int32, FString> ParamStringsMap =
		{
			{-1, TEXT("_TooManyParams")},
			{0, TEXT("")},
			{1, TEXT("_OneParam")},
			{2, TEXT("_TwoParams")},
			{3, TEXT("_ThreeParams")},
			{4, TEXT("_FourParams")},
			{5, TEXT("_FiveParams")},
			{6, TEXT("_SixParams")},
			{7, TEXT("_SevenParams")},
			{8, TEXT("_EightParams")},
			{9, TEXT("_NineParams")}
		};

		const FString* NumParamsString = ParamStringsMap.Find(SigFunction->NumParms);
		if (!NumParamsString)
		{
			NumParamsString = &ParamStringsMap[-1];
		}

		TArray<FString> MacroParams;
		MacroParams.Emplace(GetCPPTypenameForProperty(&DelegateProp));

		for (TFieldIterator<FProperty> ParamIt(SigFunction); ParamIt; ++ParamIt)
		{
			MacroParams.Emplace(GetCPPTypenameForProperty(*ParamIt));
			if (ParamIt->HasAnyPropertyFlags(CPF_ReferenceParm))
			{
				MacroParams.Last().Append(TEXT("&"));
			}

			MacroParams.Emplace(ParamIt->GetAuthoredName());
		}

		RawItemString += FString::Printf(TEXT("\nDECLARE_DYNAMIC_MULTICAST_DELEGATE%s(%s);"), **NumParamsString, *FString::Join(MacroParams, TEXT(", ")));

		// Add rich text decorators for macro parameters
		for (int32 ParamIdx = 0; ParamIdx < MacroParams.Num(); ++ParamIdx)
		{
			// the delegate name (idx 0) and parameter types (odd number idx) are typename, all other parameters are identifiers
			const bool bIsTypename = ParamIdx == 0 || ParamIdx % 2 != 0;
			MacroParams[ParamIdx] = FString::Printf(TEXT("<%s>%s</>"), bIsTypename ? *GBA::HeaderViewSyntaxDecorators::TypenameDecorator : *GBA::HeaderViewSyntaxDecorators::IdentifierDecorator, *MacroParams[ParamIdx]);
		}

		RichTextString += FString::Printf(TEXT("\n<%s>DECLARE_DYNAMIC_MULTICAST_DELEGATE%s</>(%s);"), *GBA::HeaderViewSyntaxDecorators::MacroDecorator, **NumParamsString, *FString::Join(MacroParams, TEXT(", ")));
	}
}

FString FGBAHeaderViewVariableListItem::GetConditionalUPropertySpecifiers(const FProperty& VarProperty) const
{
	TArray<FString> PropertySpecifiers;

	if (!VarProperty.HasMetaData(FBlueprintMetadata::MD_Private) || !VarProperty.GetBoolMetaData(FBlueprintMetadata::MD_Private))
	{
		if (VarProperty.HasAnyPropertyFlags(CPF_BlueprintAssignable))
		{
			PropertySpecifiers.Emplace(TEXT("BlueprintAssignable"));
		}
		else if (VarProperty.HasAnyPropertyFlags(CPF_Edit))
		{
			PropertySpecifiers.Emplace(TEXT("BlueprintReadWrite"));
		}
		else
		{
			PropertySpecifiers.Emplace(TEXT("BlueprintReadOnly"));
		}
	}

	if (!VarProperty.HasAnyPropertyFlags(CPF_Edit))
	{
		PropertySpecifiers.Emplace(TEXT("VisibleAnywhere"));
	}
	else if (!VarProperty.HasAnyPropertyFlags(CPF_DisableEditOnInstance | CPF_DisableEditOnTemplate))
	{
		PropertySpecifiers.Emplace(TEXT("EditAnywhere"));
	}
	else if (VarProperty.HasAnyPropertyFlags(CPF_DisableEditOnInstance))
	{
		PropertySpecifiers.Emplace(TEXT("EditDefaultsOnly"));
	}
	else
	{
		PropertySpecifiers.Emplace(TEXT("EditInstanceOnly"));
	}

	if (VarProperty.HasMetaData(FBlueprintMetadata::MD_FunctionCategory))
	{
		PropertySpecifiers.Emplace(FString::Printf(TEXT("Category=\"%s\""), *VarProperty.GetMetaData(FBlueprintMetadata::MD_FunctionCategory)));
	}

	if (VarProperty.HasAnyPropertyFlags(CPF_Net))
	{
		if (VarProperty.HasAnyPropertyFlags(CPF_RepNotify))
		{
			PropertySpecifiers.Emplace(FString::Printf(TEXT("ReplicatedUsing=\"OnRep_%s\""), *VarProperty.GetAuthoredName()));
		}
		else
		{
			PropertySpecifiers.Emplace(TEXT("Replicated"));
		}
	}

	if (VarProperty.HasAnyPropertyFlags(CPF_Interp))
	{
		PropertySpecifiers.Emplace(TEXT("Interp"));
	}

	if (VarProperty.HasAnyPropertyFlags(CPF_Config))
	{
		PropertySpecifiers.Emplace(TEXT("Config"));
	}

	if (VarProperty.HasAnyPropertyFlags(CPF_Transient))
	{
		PropertySpecifiers.Emplace(TEXT("Transient"));
	}

	if (VarProperty.HasAnyPropertyFlags(CPF_SaveGame))
	{
		PropertySpecifiers.Emplace(TEXT("SaveGame"));
	}

	if (VarProperty.HasAnyPropertyFlags(CPF_AdvancedDisplay))
	{
		PropertySpecifiers.Emplace(TEXT("AdvancedDisplay"));
	}

	if (VarProperty.HasMetaData(FEdMode::MD_MakeEditWidget) && VarProperty.GetBoolMetaData(FEdMode::MD_MakeEditWidget))
	{
		PropertySpecifiers.Emplace(TEXT("MakeEditWidget"));
	}

	// meta specifiers
	{
		if (const TMap<FName, FString>* MetaDataMap = VarProperty.GetMetaDataMap())
		{
			// These metadata keys are handled explicitly elsewhere
			static const TArray IgnoreMetaData = 
			{
				FBlueprintMetadata::MD_DeprecationMessage,
				FBlueprintMetadata::MD_FunctionCategory,
				FBlueprintMetadata::MD_Tooltip,
				FBlueprintMetadata::MD_Private,
				FBlueprintMetadata::MD_Private,
				FEdMode::MD_MakeEditWidget,

				// This gets added even to non FText
				FName(TEXT("MultiLine"))
			};

			TArray<FString> MetaSpecifiers;

			for (const TPair<FName, FString>& MetaPair : *MetaDataMap)
			{
				// Don't take this metadata if we handled it explicitly
				if (IgnoreMetaData.Contains(MetaPair.Key))
				{
					continue;
				}

				// Don't add the DisplayName metadata key if the display name is just the friendly name generated by the editor anyway
				if (MetaPair.Key == FBlueprintMetadata::MD_DisplayName)
				{
					if (MetaPair.Value == FName::NameToDisplayString(VarProperty.GetName(), !!CastField<FBoolProperty>(&VarProperty)))
					{
						continue;
					}
				}

				MetaSpecifiers.Emplace(FString::Printf(TEXT("%s=\"%s\""), *MetaPair.Key.ToString(), *MetaPair.Value));
			}

			if (!MetaSpecifiers.IsEmpty())
			{
				PropertySpecifiers.Emplace(FString::Printf(TEXT("meta=(%s)"), *FString::Join(MetaSpecifiers, TEXT(", "))));
			}
		}
	}

	return FString::Join(PropertySpecifiers, TEXT(", "));
}

FString FGBAHeaderViewVariableListItem::GetOwningClassName(const FProperty& VarProperty)
{
	const UClass* OwningClass = VarProperty.GetOwnerClass();
	if (OwningClass && OwningClass->ClassGeneratedBy)
	{
		return OwningClass->GetPrefixCPP() + OwningClass->ClassGeneratedBy->GetName();
	}

	return TEXT("");
}

bool FGBAHeaderViewVariableListItem::OnVerifyRenameTextChanged(const FText& InNewName, FText& OutErrorText, const TWeakObjectPtr<UObject> WeakAsset) const
{
	if (!IsValidCPPIdentifier(InNewName.ToString()))
	{
		OutErrorText = InvalidCPPIdentifierErrorText;
		return false;
	}

	UObject* Asset = WeakAsset.Get();

	if (const UBlueprint* Blueprint = Cast<UBlueprint>(Asset))
	{
		FKismetNameValidator NameValidator(Blueprint, NAME_None, nullptr);
		const EValidatorResult Result = NameValidator.IsValid(InNewName.ToString());
		if (Result != EValidatorResult::Ok)
		{
			OutErrorText = GetErrorTextFromValidatorResult(Result);
			return false;
		}

		return true;
	}

	if (const UUserDefinedStruct* Struct = Cast<UUserDefinedStruct>(Asset))
	{
		return FStructureEditorUtils::IsUniqueVariableFriendlyName(Struct, InNewName.ToString());
	}

	return false;
}

void FGBAHeaderViewVariableListItem::OnRenameTextCommitted(const FText& CommittedText, const ETextCommit::Type TextCommitType, const TWeakObjectPtr<UObject> WeakAsset) const
{
	if (TextCommitType == ETextCommit::OnEnter)
	{
		if (UObject* Asset = WeakAsset.Get())
		{
			const FString& CommittedString = CommittedText.ToString();
			if (IsValidCPPIdentifier(CommittedString))
			{
				if (UBlueprint* Blueprint = Cast<UBlueprint>(Asset))
				{
					FBlueprintEditorUtils::RenameMemberVariable(Blueprint, IllegalName, FName(CommittedString));
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
