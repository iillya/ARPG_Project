// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAHeaderViewClassListItem.h"
#include "AssetToolsModule.h"
#include "AssetViewUtils.h"
#include "Engine/Blueprint.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "LineEndings/GBALineEndings.h"
#include "Misc/EngineVersionComparison.h"
#include "Models/GBAAttributeSetWizardViewModel.h"

#define LOCTEXT_NAMESPACE "FGBAHeaderViewClassListItem"

FGBAHeaderViewClassListItem::FGBAHeaderViewClassListItem(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	check(InViewModel.IsValid());
	
	if (const UBlueprint* Blueprint = InViewModel->GetSelectedBlueprint().Get())
	{
		const FString DesiredClassName = InViewModel->GetNewClassName();
		const FNewClassInfo ParentClassInfo = InViewModel->GetParentClassInfo();
		const GameProjectUtils::EClassLocation ClassLocation = InViewModel->GetClassLocation();
		const TSharedPtr<FModuleContextInfo> ModuleInfo = InViewModel->GetSelectedModuleInfo();
		
		// Avoid lots of reallocations
		RawItemString.Reserve(512);
		RichTextString.Reserve(512);

		// Format comment
		{
			const FString Comment = Blueprint->BlueprintDescription.IsEmpty() ? TEXT("Please add a class description") : Blueprint->BlueprintDescription;
			FormatCommentString(Comment, RawItemString, RichTextString);
		}

		// Add the UCLASS specifiers
		// i.e. UCLASS(Blueprintable, BlueprintType, Category=BlueprintCategory)
		{
			const FString AdditionalSpecifiers = GetConditionalUClassSpecifiers(Blueprint);

			// Always add Blueprintable and BlueprintType
			// TODO: Only BlueprintType ?
			// RawItemString += FString::Printf(TEXT("\nUCLASS(Blueprintable, BlueprintType%s)"), *AdditionalSpecifiers);
			// RichTextString += FString::Printf(TEXT("\n<%s>UCLASS</>(Blueprintable, BlueprintType%s)"), *GBA::HeaderViewSyntaxDecorators::MacroDecorator, *AdditionalSpecifiers);

			RawItemString += FString::Printf(TEXT("\nUCLASS(BlueprintType%s)"), *AdditionalSpecifiers);
			RichTextString += FString::Printf(TEXT("\n<%s>UCLASS</>(BlueprintType%s)"), *GBA::HeaderViewSyntaxDecorators::MacroDecorator, *AdditionalSpecifiers);
		}

		// Add the class declaration line
		// i.e. class ClassName : public ParentClass
		{
			const FString ClassName = GetClassNameToGenerate(Blueprint, DesiredClassName);
			const FString ParentClassName = ParentClassInfo.BaseClass ? ParentClassInfo.BaseClass->GetPrefixCPP() + ParentClassInfo.BaseClass->GetName() : TEXT("UAttributeSet");

			bIsValidName = IsValidCPPIdentifier(ClassName);
			const FString& NameDecorator = bIsValidName ? GBA::HeaderViewSyntaxDecorators::TypenameDecorator : GBA::HeaderViewSyntaxDecorators::ErrorDecorator;

			FString MacroExportAPI;
			FString MacroRichTextExportAPI;
			if (ClassLocation == GameProjectUtils::EClassLocation::Public && ModuleInfo.IsValid())
			{
				MacroExportAPI = FString::Printf(TEXT(" %s_API"), *ModuleInfo->ModuleName.ToUpper());
				MacroRichTextExportAPI = FString::Printf(TEXT(" <%s>%s_API</>"), *GBA::HeaderViewSyntaxDecorators::MacroDecorator, *ModuleInfo->ModuleName.ToUpper());
			}

			RawItemString += FString::Printf(TEXT("\nclass%s %s : public %s\n{\n\tGENERATED_BODY()"), *MacroExportAPI, *ClassName, *ParentClassName);
			RichTextString += FString::Printf(TEXT("\n<%s>class</>%s <%s>%s</> : <%s>public</> <%s>%s</>\n{\n\t<%s>GENERATED_BODY</>()"),
				*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
				*MacroRichTextExportAPI,
				*NameDecorator,
				*ClassName,
				*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
				*GBA::HeaderViewSyntaxDecorators::TypenameDecorator,
				*ParentClassName,
				*GBA::HeaderViewSyntaxDecorators::MacroDecorator
			);
		}

		// normalize to platform newlines
		GBA::String::ToHostLineEndingsInline(RawItemString);
		GBA::String::ToHostLineEndingsInline(RichTextString);
	}
}

FGBAHeaderViewListItemPtr FGBAHeaderViewClassListItem::Create(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	return MakeShared<FGBAHeaderViewClassListItem>(InViewModel);
}

void FGBAHeaderViewClassListItem::ExtendContextMenu(FMenuBuilder& InMenuBuilder, const TWeakObjectPtr<UObject> InAsset)
{
	if (!bIsValidName)
	{
#if UE_VERSION_NEWER_THAN(5, 1, -1)
		if (UBlueprint* Blueprint = Cast<UBlueprint>(InAsset.Get()))
		{
			const TWeakObjectPtr<UBlueprint> WeakBlueprint = Blueprint;
			InMenuBuilder.AddVerifiedEditableText(LOCTEXT("RenameBlueprint", "Rename Blueprint"),
				LOCTEXT("RenameItemTooltip", "Renames this Blueprint\nThis Blueprint name is not a legal C++ identifier."),
				FSlateIcon(),
				FText::FromString(Blueprint->GetName()),
				FOnVerifyTextChanged::CreateSP(this, &FGBAHeaderViewClassListItem::OnVerifyRenameTextChanged, WeakBlueprint),
				FOnTextCommitted::CreateSP(this, &FGBAHeaderViewClassListItem::OnRenameTextCommitted, WeakBlueprint)
			);
		}
#endif
	}
}

FString FGBAHeaderViewClassListItem::GetConditionalUClassSpecifiers(const UBlueprint* Blueprint)
{
	TStringBuilder<256> AdditionalSpecifiers;

	if (Blueprint->bGenerateConstClass)
	{
		AdditionalSpecifiers.Append(TEXT(", Const"));
	}

	if (Blueprint->bGenerateAbstractClass)
	{
		AdditionalSpecifiers.Append(TEXT(", Abstract"));
	}

	if (!Blueprint->BlueprintCategory.IsEmpty())
	{
		AdditionalSpecifiers.Append(FString::Printf(TEXT(", Category=\"%s\""), *Blueprint->BlueprintCategory));
	}

	if (!Blueprint->HideCategories.IsEmpty())
	{
		AdditionalSpecifiers.Append(TEXT(", HideCategories=("));

		for (int32 HideCategoryIdx = 0; HideCategoryIdx < Blueprint->HideCategories.Num(); ++HideCategoryIdx)
		{
			if (HideCategoryIdx == 0)
			{
				AdditionalSpecifiers.Append(FString::Printf(TEXT("\"%s\""), *Blueprint->HideCategories[HideCategoryIdx]));
			}
			else
			{
				AdditionalSpecifiers.Append(FString::Printf(TEXT(", \"%s\""), *Blueprint->HideCategories[HideCategoryIdx]));
			}
		}

		AdditionalSpecifiers.Append(TEXT(")"));
	}

	if (!Blueprint->BlueprintDisplayName.IsEmpty() || !Blueprint->BlueprintNamespace.IsEmpty())
	{
		AdditionalSpecifiers.Append(TEXT(", meta=("));

		int32 SpecifierCount = 0;

		if (!Blueprint->BlueprintDisplayName.IsEmpty())
		{
			AdditionalSpecifiers.Append(FString::Printf(TEXT("DisplayName=\"%s\""), *Blueprint->BlueprintDisplayName));
			++SpecifierCount;
		}

		if (!Blueprint->BlueprintNamespace.IsEmpty())
		{
			if (SpecifierCount > 0)
			{
				AdditionalSpecifiers.Append(FString::Printf(TEXT(", Namespace=\"%s\""), *Blueprint->BlueprintNamespace));
			}
			else
			{
				AdditionalSpecifiers.Append(FString::Printf(TEXT("Namespace=\"%s\""), *Blueprint->BlueprintNamespace));
			}
		}

		AdditionalSpecifiers.Append(TEXT(")"));
	}

	return AdditionalSpecifiers.ToString();
}

FString FGBAHeaderViewClassListItem::GetRenamedBlueprintPath(const UBlueprint* Blueprint, const FString& NewName) const
{
	check(Blueprint);
	FString NewPath = Blueprint->GetPathName();
	int32 Index = 0;
	if (!ensure(NewPath.FindLastChar(TEXT('/'), Index)))
	{
		// AssetViewUtils::IsValidObjectPathForCreate will return false for an empty string
		return TEXT("");
	}
	NewPath.LeftInline(Index);
	NewPath /= FString::Printf(TEXT("%s.%s"), *NewName, *NewName);
	return NewPath;
}

bool FGBAHeaderViewClassListItem::OnVerifyRenameTextChanged(const FText& InNewName, FText& OutErrorText, const TWeakObjectPtr<UBlueprint> InBlueprint) const
{
	if (const UBlueprint* Blueprint = InBlueprint.Get())
	{
		const FString NewPath = GetRenamedBlueprintPath(Blueprint, InNewName.ToString());
		if (!AssetViewUtils::IsValidObjectPathForCreate(NewPath, Blueprint->GetClass(), OutErrorText))
		{
			return false;
		}

		if (!IsValidCPPIdentifier(InNewName.ToString()))
		{
			OutErrorText = InvalidCPPIdentifierErrorText;
			return false;
		}

		return true;
	}

	return false;
}

void FGBAHeaderViewClassListItem::OnRenameTextCommitted(const FText& CommittedText, const ETextCommit::Type TextCommitType, const TWeakObjectPtr<UBlueprint> InBlueprint) const
{
	if (TextCommitType == ETextCommit::OnEnter)
	{
		FText ErrorText;
		if (OnVerifyRenameTextChanged(CommittedText, ErrorText, InBlueprint))
		{
			if (UBlueprint* Blueprint = InBlueprint.Get())
			{
				const FString NewPath = GetRenamedBlueprintPath(Blueprint, CommittedText.ToString());
				const FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
				const TArray AssetToRename = { FAssetRenameData(Blueprint, NewPath) };
				AssetToolsModule.Get().RenameAssets(AssetToRename);
				FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
