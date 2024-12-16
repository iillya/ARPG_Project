// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAHeaderViewFunctionListItem.h"

#include "GBAScaffoldLog.h"
#include "K2Node_FunctionEntry.h"
#include "Engine/Blueprint.h"
#include "Framework/SlateDelegates.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "LineEndings/GBALineEndings.h"
#include "Misc/EngineVersion.h"
#include "Misc/EngineVersionComparison.h"

#define LOCTEXT_NAMESPACE "FGBAHeaderViewFunctionListItem"

FGBAHeaderViewListItemPtr FGBAHeaderViewFunctionListItem::Create(const UK2Node_FunctionEntry* FunctionEntry)
{
	return MakeShareable(new FGBAHeaderViewFunctionListItem(FunctionEntry));
}

void FGBAHeaderViewFunctionListItem::ExtendContextMenu(FMenuBuilder& InMenuBuilder, const TWeakObjectPtr<UObject> InAsset)
{
	if (UBlueprint* Blueprint = Cast<UBlueprint>(InAsset.Get()))
	{
		const TWeakObjectPtr<UBlueprint> WeakBlueprint = Blueprint;
		InMenuBuilder.AddMenuEntry(LOCTEXT("JumpToDefinition", "Jump to Definition"),
			LOCTEXT("JumpToDefinitionTooltip", "Opens this function in the Blueprint Editor"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateSP(this, &FGBAHeaderViewFunctionListItem::JumpToDefinition, WeakBlueprint))
		);

#if UE_VERSION_NEWER_THAN(5, 1, -1)
		if (!IllegalName.IsNone())
		{
			InMenuBuilder.AddVerifiedEditableText(LOCTEXT("RenameItem", "Rename Function"),
				LOCTEXT("RenameItemTooltip", "Renames this function in the Blueprint\nThis function name is not a legal C++ identifier."),
				FSlateIcon(),
				FText::FromName(IllegalName),
				FOnVerifyTextChanged::CreateStatic(&FGBAHeaderViewFunctionListItem::OnVerifyRenameFunctionTextChanged, WeakBlueprint),
				FOnTextCommitted::CreateStatic(&FGBAHeaderViewFunctionListItem::OnRenameFunctionTextCommitted, WeakBlueprint, GraphName)
			);
		}

		for (FName IllegalParam : IllegalParameters)
		{
			InMenuBuilder.AddVerifiedEditableText(LOCTEXT("RenameParm", "Rename Parameter"),
				LOCTEXT("RenameParmTooltip", "Renames this function parameter in the Blueprint\nThis parameter name is not a legal C++ identifier."),
				FSlateIcon(),
				FText::FromName(IllegalParam),
				FOnVerifyTextChanged::CreateSP(this, &FGBAHeaderViewFunctionListItem::OnVerifyRenameParameterTextChanged, WeakBlueprint, GraphName),
				FOnTextCommitted::CreateSP(this, &FGBAHeaderViewFunctionListItem::OnRenameParameterTextCommitted, WeakBlueprint, GraphName, IllegalParam)
			);
		}
#endif
	}
}

void FGBAHeaderViewFunctionListItem::OnMouseButtonDoubleClick(const TWeakObjectPtr<UObject> InAsset)
{
	const TWeakObjectPtr<UBlueprint> WeakBlueprint = Cast<UBlueprint>(InAsset.Get());
	JumpToDefinition(WeakBlueprint);
}

FString FGBAHeaderViewFunctionListItem::GetConditionalUFunctionSpecifiers(const UFunction* SigFunction)
{
	check(SigFunction);

	TStringBuilder<256> AdditionalSpecifiers;

	if (SigFunction->FunctionFlags & FUNC_BlueprintPure)
	{
		AdditionalSpecifiers.Append(TEXT("BlueprintPure"));
	}
	else
	{
		AdditionalSpecifiers.Append(TEXT("BlueprintCallable"));
	}

	if (SigFunction->GetBoolMetaData(FBlueprintMetadata::MD_CallInEditor))
	{
		AdditionalSpecifiers.Append(TEXT(", CallInEditor"));
	}

	if (SigFunction->FunctionFlags & FUNC_Exec)
	{
		AdditionalSpecifiers.Append(TEXT(", Exec"));
	}

	const FString& Category = SigFunction->GetMetaData(FBlueprintMetadata::MD_FunctionCategory);
	if (!Category.IsEmpty())
	{
		AdditionalSpecifiers.Append(FString::Printf(TEXT(", Category=\"%s\""), *Category));
	}

	// Meta Specifiers
	{
		TArray<FString> MetaSpecifiers;

		if (SigFunction->GetBoolMetaData(FBlueprintMetadata::MD_ThreadSafe))
		{
			MetaSpecifiers.Emplace(TEXT("BlueprintThreadSafe"));
		}

		const FString& CompactNodeTitle = SigFunction->GetMetaData(FBlueprintMetadata::MD_CompactNodeTitle);
		if (!CompactNodeTitle.IsEmpty())
		{
			MetaSpecifiers.Emplace(FString::Printf(TEXT("CompactNodeTitle=\"%s\""), *CompactNodeTitle));
		}

		const FString& DisplayName = SigFunction->GetMetaData(FBlueprintMetadata::MD_DisplayName);
		if (!DisplayName.IsEmpty())
		{
			MetaSpecifiers.Emplace(FString::Printf(TEXT("DisplayName=\"%s\""), *DisplayName));
		}
		
		const FString& Keywords = SigFunction->GetMetaData(FBlueprintMetadata::MD_FunctionKeywords);
		if (!Keywords.IsEmpty())
		{
			MetaSpecifiers.Emplace(FString::Printf(TEXT("Keywords=\"%s\""), *Keywords));
		}

		if (!MetaSpecifiers.IsEmpty())
		{
			AdditionalSpecifiers.Append(FString::Printf(TEXT(", meta=(%s)"), *FString::Join(MetaSpecifiers, TEXT(", "))));
		}
	}

	return AdditionalSpecifiers.ToString();
}

void FGBAHeaderViewFunctionListItem::AppendFunctionParameters(const UFunction* SignatureFunction)
{
	check(SignatureFunction);

	TArray<FString> Parameters;

	// cache the return property to check against later
	const FProperty* ReturnProperty = SignatureFunction->GetReturnProperty();

	int32 ParamIdx = 0;
	for (TFieldIterator<const FProperty> ParamIt(SignatureFunction); ParamIt; ++ParamIt)
	{
		// ReturnValue property shouldn't be duplicated in the parameter list
		if (*ParamIt == ReturnProperty)
		{
			continue;
		}

		if (ParamIdx > 0)
		{
			RawItemString.Append(TEXT(", "));
			RichTextString.Append(TEXT(", "));
		}

		if (ParamIt->HasAnyPropertyFlags(CPF_ConstParm))
		{
			RawItemString.Append(TEXT("const "));
			RichTextString.Append(FString::Printf(TEXT("<%s>const</> "), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator));
		}
		// If a param is declared as const&, then it is already treated as input and UPARAM(ref) will just be clutter
		else if (ParamIt->HasAnyPropertyFlags(CPF_ReferenceParm))
		{
			RawItemString.Append(TEXT("UPARAM(ref) "));
			RichTextString.Append(FString::Printf(TEXT("<%s>UPARAM</>(ref) "), *GBA::HeaderViewSyntaxDecorators::MacroDecorator));
		}

		const FString Typename = GetCPPTypenameForProperty(*ParamIt);
		const FString ParamName = ParamIt->GetAuthoredName();
		
		const bool bIsValidName = IsValidCPPIdentifier(ParamName);
		const FString* IdentifierDecorator = &GBA::HeaderViewSyntaxDecorators::IdentifierDecorator;
		if (!bIsValidName)
		{
			IllegalParameters.Emplace(ParamName);
			IdentifierDecorator = &GBA::HeaderViewSyntaxDecorators::ErrorDecorator;
		}

		if (ParamIt->HasAnyPropertyFlags(CPF_OutParm | CPF_ReferenceParm))
		{
			RawItemString.Append(FString::Printf(TEXT("%s& %s"), *Typename, *ParamName));
			RichTextString.Append(FString::Printf(TEXT("<%s>%s</>& <%s>%s</>"), *GBA::HeaderViewSyntaxDecorators::TypenameDecorator, *Typename, **IdentifierDecorator, *ParamName));
		}
		else
		{
			RawItemString.Append(FString::Printf(TEXT("%s %s"), *Typename, *ParamName));
			RichTextString.Append(FString::Printf(TEXT("<%s>%s</> <%s>%s</>"), *GBA::HeaderViewSyntaxDecorators::TypenameDecorator, *Typename, **IdentifierDecorator, *ParamName));
		}

		++ParamIdx;
	}
}

FGBAHeaderViewFunctionListItem::FGBAHeaderViewFunctionListItem(const UK2Node_FunctionEntry* FunctionEntry)
{
	check(FunctionEntry);

	GraphName = FunctionEntry->GetGraph()->GetFName();
	RawItemString.Reserve(512);
	RichTextString.Reserve(512);

	if (const UFunction* ResolvedFunc = FunctionEntry->FindSignatureFunction())
	{
		// Format comment
		{
			FString Comment = ResolvedFunc->GetMetaData(FBlueprintMetadata::MD_Tooltip);
			if (Comment.IsEmpty())
			{
				Comment = TEXT("Please add a function description");
			}

			if (ResolvedFunc->HasAnyFunctionFlags(FUNC_Event))
			{
				const UClass* OriginClass = ResolvedFunc->GetOwnerClass();
				const FString OriginClassName = OriginClass->GetPrefixCPP() + OriginClass->GetName();
				const FString EventType = ResolvedFunc->HasAnyFunctionFlags(FUNC_Native) ? TEXT("BlueprintNativeEvent") : TEXT("BlueprintImplementableEvent");
				Comment.Append(FString::Printf(TEXT("\n\nNOTE: This function is linked to %s: %s::%s"), *EventType, *OriginClassName, *ResolvedFunc->GetName()));
			}

			FormatCommentString(Comment, RawItemString, RichTextString);
		}

		// Add Deprecation message if present
		if (ResolvedFunc->GetBoolMetaData(FBlueprintMetadata::MD_DeprecatedFunction))
		{
			FString DeprecationMessage = ResolvedFunc->GetMetaData(FBlueprintMetadata::MD_DeprecationMessage);
			if (DeprecationMessage.IsEmpty())
			{
				DeprecationMessage = TEXT("Please add a deprecation message.");
			}

			const FString EngineVersionString = FEngineVersion::Current().ToString(EVersionComponent::Patch);

			RawItemString += FString::Printf(TEXT("\nUE_DEPRECATED(%s, \"%s\")"), *EngineVersionString, *DeprecationMessage);
			RichTextString += FString::Printf(TEXT("\n<%s>UE_DEPRECATED</>(%s, \"%s\")"), *GBA::HeaderViewSyntaxDecorators::MacroDecorator, *EngineVersionString, *DeprecationMessage);
		}

		// Add the UFUNCTION specifiers
		// i.e. UFUNCTION(BlueprintCallable, Category="Function Category")
		{
			const FString AdditionalSpecifiers = GetConditionalUFunctionSpecifiers(ResolvedFunc);

			// Always add Blueprintable and BlueprintType
			RawItemString += FString::Printf(TEXT("\nUFUNCTION(%s)"), *AdditionalSpecifiers);
			RichTextString += FString::Printf(TEXT("\n<%s>UFUNCTION</>(%s)"), *GBA::HeaderViewSyntaxDecorators::MacroDecorator, *AdditionalSpecifiers);
		}

		// Add the function declaration line
		// i.e. void FunctionName(Type InParam1, UPARAM(ref) Type2& InParam2, Type3& OutParam1)
		{
			FString FunctionName;
			if (FunctionEntry->CustomGeneratedFunctionName.IsNone())
			{
				FunctionName = ResolvedFunc->GetName();
			}
			else
			{
				FunctionName = FunctionEntry->CustomGeneratedFunctionName.ToString();
			}

			const bool bValidName = IsValidCPPIdentifier(FunctionName);
			const FString* IdentifierDecorator = &GBA::HeaderViewSyntaxDecorators::IdentifierDecorator;
			if (!bValidName)
			{
				IllegalName = ResolvedFunc->GetFName();
				IdentifierDecorator = &GBA::HeaderViewSyntaxDecorators::ErrorDecorator;
			}

			if (FProperty* ReturnProperty = ResolvedFunc->GetReturnProperty())
			{
				const FString Typename = ReturnProperty->GetCPPType();
				RawItemString += FString::Printf(TEXT("\n%s %s("), *Typename, *FunctionName);
				RichTextString += FString::Printf(TEXT("\n<%s>%s</> <%s>%s</>("), *GBA::HeaderViewSyntaxDecorators::TypenameDecorator, *Typename, **IdentifierDecorator, *FunctionName);
			}
			else
			{
				RawItemString += FString::Printf(TEXT("\nvoid %s("), *FunctionName);
				RichTextString += FString::Printf(TEXT("\n<%s>void</> <%s>%s</>("), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator, **IdentifierDecorator, *FunctionName);
			}

			AppendFunctionParameters(ResolvedFunc);

			if (FunctionEntry->GetFunctionFlags() & FUNC_Const)
			{
				RawItemString += TEXT(") const;");
				RichTextString += FString::Printf(TEXT(") <%s>const</>;"), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator);
			}
			else
			{
				RawItemString += TEXT(");");
				RichTextString += TEXT(");");
			}
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
}

void FGBAHeaderViewFunctionListItem::OnRenameFunctionTextCommitted(const FText& CommittedText, const ETextCommit::Type TextCommitType, const TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName)
{
	if (TextCommitType == ETextCommit::OnEnter)
	{
		if (UBlueprint* Blueprint = WeakBlueprint.Get())
		{
			const FString& CommittedString = CommittedText.ToString();
			if (IsValidCPPIdentifier(CommittedString))
			{
				const TObjectPtr<UEdGraph>* FunctionGraph = Blueprint->FunctionGraphs.FindByPredicate([OldGraphName](const TObjectPtr<UEdGraph>& Graph)
					{
						return Graph->GetFName() == OldGraphName;
					});

				if (FunctionGraph)
				{
					FBlueprintEditorUtils::RenameGraph(FunctionGraph->Get(), CommittedString);
				}
				else
				{
					GBA_SCAFFOLD_LOG(Warning, TEXT("Could not find Function Graph named \"%s\" in Blueprint \"%s\""), *OldGraphName.ToString(), *Blueprint->GetName());
				}
			}
		}
	}
}

bool FGBAHeaderViewFunctionListItem::OnVerifyRenameFunctionTextChanged(const FText& InNewName, FText& OutErrorText, const TWeakObjectPtr<UBlueprint> WeakBlueprint)
{
	if (const UBlueprint* Blueprint = WeakBlueprint.Get())
	{
		if (!IsValidCPPIdentifier(InNewName.ToString()))
		{
			OutErrorText = InvalidCPPIdentifierErrorText;
			return false;
		}

		FKismetNameValidator NameValidator(Blueprint, NAME_None, nullptr);
		const EValidatorResult Result = NameValidator.IsValid(InNewName.ToString());
		if (Result != EValidatorResult::Ok)
		{
			OutErrorText = GetErrorTextFromValidatorResult(Result);
			return false;
		}

		return true;
	}

	return false;
}

bool FGBAHeaderViewFunctionListItem::OnVerifyRenameParameterTextChanged(const FText& InNewName, FText& OutErrorText, const TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName) const
{
	if (const UBlueprint* Blueprint = WeakBlueprint.Get())
	{
		if (!IsValidCPPIdentifier(InNewName.ToString()))
		{
			OutErrorText = InvalidCPPIdentifierErrorText;
			return false;
		}

		const TObjectPtr<UEdGraph>* FunctionGraph = Blueprint->FunctionGraphs.FindByPredicate([OldGraphName](const TObjectPtr<UEdGraph>& Graph)
			{
				return Graph->GetFName() == OldGraphName;
			});

		if (FunctionGraph)
		{
			TArray<UK2Node_FunctionEntry*> Entry;
			FunctionGraph->Get()->GetNodesOfClass<UK2Node_FunctionEntry>(Entry);
			if (ensureMsgf(Entry.Num() == 1 && Entry[0], TEXT("Function Graph \"%s\" in Blueprint \"%s\" does not have exactly one Entry Node"), *FunctionGraph->Get()->GetName(), *Blueprint->GetName()))
			{
				FKismetNameValidator NameValidator(Blueprint, NAME_None, Entry[0]->FindSignatureFunction());
				const EValidatorResult Result = NameValidator.IsValid(InNewName.ToString());
				if (Result != EValidatorResult::Ok)
				{
					OutErrorText = GetErrorTextFromValidatorResult(Result);
					return false;
				}
			}
		}

		return true;
	}

	return false;
}

void FGBAHeaderViewFunctionListItem::OnRenameParameterTextCommitted(const FText& CommittedText, const ETextCommit::Type TextCommitType, const TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName, const FName OldParamName) const
{
	if (TextCommitType == ETextCommit::OnEnter)
	{
		if (UBlueprint* Blueprint = WeakBlueprint.Get())
		{
			const FString& CommittedString = CommittedText.ToString();
			if (IsValidCPPIdentifier(CommittedString))
			{
				const TObjectPtr<UEdGraph>* FunctionGraph = Blueprint->FunctionGraphs.FindByPredicate([OldGraphName](const TObjectPtr<UEdGraph>& Graph)
					{
						return Graph->GetFName() == OldGraphName;
					});

				if (FunctionGraph)
				{
					TArray<UK2Node_FunctionEntry*> Entry;
					FunctionGraph->Get()->GetNodesOfClass<UK2Node_FunctionEntry>(Entry);
					if (ensureMsgf(Entry.Num() == 1 && Entry[0], TEXT("Function Graph \"%s\" in Blueprint \"%s\" does not have exactly one Entry Node"), *FunctionGraph->Get()->GetName(), *Blueprint->GetName()))
					{
						if (Entry[0]->RenameUserDefinedPin(OldParamName, FName(CommittedString)) == ERenamePinResult_Success)
						{
							FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
						}
					}
				}
				else
				{
					GBA_SCAFFOLD_LOG(Warning, TEXT("Could not find Function Graph named \"%s\" in Blueprint \"%s\""), *OldGraphName.ToString(), *Blueprint->GetName());
				}
			}
		}
	}
}

void FGBAHeaderViewFunctionListItem::JumpToDefinition(const TWeakObjectPtr<UBlueprint> WeakBlueprint) const
{
	if (const UBlueprint* Blueprint = WeakBlueprint.Get())
	{
		const TObjectPtr<UEdGraph>* FunctionGraph = Blueprint->FunctionGraphs.FindByPredicate([GraphName=GraphName](const TObjectPtr<UEdGraph>& Graph)
			{
				return Graph->GetFName() == GraphName;
			});

		if (FunctionGraph)
		{
			TArray<UK2Node_FunctionEntry*> Entry;
			FunctionGraph->Get()->GetNodesOfClass<UK2Node_FunctionEntry>(Entry);
			if (ensureMsgf(Entry.Num() == 1 && Entry[0], TEXT("Function Graph \"%s\" in Blueprint \"%s\" does not have exactly one Entry Node"), *FunctionGraph->Get()->GetName(), *Blueprint->GetName()))
			{
				FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(Entry[0]);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
