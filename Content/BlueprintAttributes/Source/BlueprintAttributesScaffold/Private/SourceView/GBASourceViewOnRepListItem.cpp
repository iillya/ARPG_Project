// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBASourceViewOnRepListItem.h"

#include "LineEndings/GBALineEndings.h"
#include "Models/GBAAttributeSetWizardViewModel.h"

#define LOCTEXT_NAMESPACE "FGBASourceViewOnRepListItem"

FGBAHeaderViewListItemPtr FGBASourceViewOnRepListItem::Create(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel, const FProperty& InProperty)
{
	return MakeShared<FGBASourceViewOnRepListItem>(InViewModel, InProperty);
}

void FGBASourceViewOnRepListItem::ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset)
{
}

FGBASourceViewOnRepListItem::FGBASourceViewOnRepListItem(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel, const FProperty& InProperty)
{
	check(InViewModel.IsValid());
	
	if (!InViewModel->GetSelectedBlueprint().IsValid())
	{
		return;
	}

	const UBlueprint* Blueprint = InViewModel->GetSelectedBlueprint().Get();
	const FString DesiredClassName = GetClassNameToGenerate(Blueprint, InViewModel->GetNewClassName());
	const FString VarName = InProperty.GetAuthoredName();

	// Add the function declaration line
	// i.e. void UDesiredClassName::OnRep_AttributeName(const FGameplayAttributeData& OldVarName)
	{
		const FString Typename = GetCPPTypenameForProperty(&InProperty, /*bIsMemberProperty=*/true);
		const bool bLegalName = IsValidCPPIdentifier(VarName);

		const FString* IdentifierDecorator = &GBA::HeaderViewSyntaxDecorators::IdentifierDecorator;
		if (!bLegalName)
		{
			IllegalName = FName(VarName);
			IdentifierDecorator = &GBA::HeaderViewSyntaxDecorators::ErrorDecorator;
		}

		if (ShouldUseConstRef(Typename))
		{
			RawItemString += FString::Printf(TEXT("void %s::OnRep_%s(const %s& Old%s)\n"), *DesiredClassName, *VarName, *Typename, *VarName);
			RichTextString += FString::Printf(
				TEXT("<%s>void</> <%s>%s</>::<%s>OnRep_%s</>(<%s>const</> <%s>%s</>& <%s>Old%s</>)\n"),
				*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
				*GBA::HeaderViewSyntaxDecorators::TypenameDecorator,
				*DesiredClassName,
				**IdentifierDecorator,
				*VarName,
				*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
				*GBA::HeaderViewSyntaxDecorators::TypenameDecorator,
				*Typename,
				**IdentifierDecorator,
				*VarName
			);
		}
		else
		{
			RawItemString += FString::Printf(TEXT("void %s::OnRep_%s(%s Old%s)\n"), *DesiredClassName, *VarName, *Typename, *VarName);
			RichTextString += FString::Printf(
				TEXT("<%s>void</> <%s>%s</>::<%s>OnRep_%s</>(<%s>%s</> <%s>Old%s</>)\n"),
				*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
				*GBA::HeaderViewSyntaxDecorators::TypenameDecorator,
				*DesiredClassName,
				**IdentifierDecorator,
				*VarName,
				*GBA::HeaderViewSyntaxDecorators::TypenameDecorator,
				*Typename,
				**IdentifierDecorator,
				*VarName
			);
		}
	}

	// Add opening brace line
	RawItemString += TEXT("\n{\n");
	RichTextString += TEXT("\n{\n");

	// Add macro definition
	{
		RawItemString += FString::Printf(
			TEXT("\tGAMEPLAYATTRIBUTE_REPNOTIFY(%s, %s, Old%s);\n"),
			*DesiredClassName,
			*VarName,
			*VarName
		);
		RichTextString += FString::Printf(
			TEXT("\t<%s>GAMEPLAYATTRIBUTE_REPNOTIFY</>(<%s>%s</>, <%s>%s</>, Old%s);\n"),
			*GBA::HeaderViewSyntaxDecorators::MacroDecorator,
			*GBA::HeaderViewSyntaxDecorators::TypenameDecorator,
			*DesiredClassName,
			*GBA::HeaderViewSyntaxDecorators::IdentifierDecorator,
			*VarName,
			*VarName
		);
	}

	// Add closing brace line
	RawItemString += TEXT("}\n");
	RichTextString += TEXT("}\n");

	// normalize to platform newlines
	GBA::String::ToHostLineEndingsInline(RawItemString);
	GBA::String::ToHostLineEndingsInline(RichTextString);
}

#undef LOCTEXT_NAMESPACE
