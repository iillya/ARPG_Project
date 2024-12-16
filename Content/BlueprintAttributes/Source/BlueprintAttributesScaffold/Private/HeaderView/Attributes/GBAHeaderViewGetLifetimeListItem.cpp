// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAHeaderViewGetLifetimeListItem.h"

#include "LineEndings/GBALineEndings.h"
#include "Models/GBAAttributeSetWizardViewModel.h"

#define LOCTEXT_NAMESPACE "FGBAHeaderViewGetLifetimeListItem"

void FGBAHeaderViewGetLifetimeListItem::ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset)
{
}

FGBAHeaderViewGetLifetimeListItem::FGBAHeaderViewGetLifetimeListItem(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	check(InViewModel.IsValid());
	
	if (const UBlueprint* Blueprint = InViewModel->GetSelectedBlueprint().Get())
	{
		// Add new line
		RawItemString += TEXT("\n");
		RichTextString += TEXT("\n");

		// Format comment
		{
			const FString ClassName = GetClassNameToGenerate(Blueprint, InViewModel->GetNewClassName());
			const FString Comment = FString::Printf(TEXT("You will need to add DOREPLIFETIME(%s, VarName) to GetLifetimeReplicatedProps"), *ClassName);

			FString RawString;
			FString RichString;
			FormatCommentString(Comment, RawString, RichString);

			RawItemString += RawString;
			RichTextString += RichString;
		}

		// Add the function declaration line
		// i.e. virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
		{
			RawItemString += TEXT("\nvirtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;");
			RichTextString += FString::Printf(
				TEXT("\n<%s>virtual</> <%s>void</> <%s>GetLifetimeReplicatedProps</>(<%s>TArray<FLifetimeProperty></>& <%s>OutLifetimeProps</>) const override;"),
				*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
				*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
				*GBA::HeaderViewSyntaxDecorators::IdentifierDecorator,
				*GBA::HeaderViewSyntaxDecorators::TypenameDecorator,
				*GBA::HeaderViewSyntaxDecorators::IdentifierDecorator
			);
		}

		// Add new line
		RawItemString += TEXT("\n");
		RichTextString += TEXT("\n");

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

FGBAHeaderViewListItemPtr FGBAHeaderViewGetLifetimeListItem::Create(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	return MakeShared<FGBAHeaderViewGetLifetimeListItem>(InViewModel);
}

#undef LOCTEXT_NAMESPACE
