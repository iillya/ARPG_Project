// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBASourceViewIncludesListItem.h"

#include "Engine/Blueprint.h"
#include "LineEndings/GBALineEndings.h"
#include "Models/GBAAttributeSetWizardViewModel.h"

#define LOCTEXT_NAMESPACE "FGBASourceViewIncludesListItem"

FGBAHeaderViewListItemPtr FGBASourceViewIncludesListItem::Create(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	return MakeShared<FGBASourceViewIncludesListItem>(InViewModel);
}

void FGBASourceViewIncludesListItem::ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset)
{
}

FGBASourceViewIncludesListItem::FGBASourceViewIncludesListItem(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	check(InViewModel.IsValid());
	
	if (const UBlueprint* Blueprint = InViewModel->GetSelectedBlueprint().Get())
	{
		const FString DesiredClassName = GetClassNameToGenerate(Blueprint, InViewModel->GetNewClassName(), false);

		FString DesiredClassPath = InViewModel->GetSelectedClassPath();
		if (!DesiredClassPath.IsEmpty() && !DesiredClassPath.EndsWith(TEXT("/")))
		{
			// Ensure trailing slash
			DesiredClassPath += TEXT("/");
		}

		// For public, include should be relative to the module. For private, should be empty (.h / .cpp should be in same Private folder)
		const FString RelativePath = InViewModel->GetClassLocation() == GameProjectUtils::EClassLocation::Public ? DesiredClassPath : TEXT("");
		const FString HeaderIncludePath = FString::Printf(TEXT("%s%s.h"), *RelativePath, *DesiredClassName);

		// Add header include for the class
		FString RawString;
		FString RichString;
		FormatIncludeDirective(HeaderIncludePath, RawString, RichString);

		RawItemString += RawString;
		RichTextString += RichString;
		
		// Add new line (between first header include and additional ones)
		RawItemString += TEXT("\n");
		RichTextString += TEXT("\n");

		const TArray<const FProperty*> ReplicatedProps = GetAllProperties(Blueprint->SkeletonGeneratedClass, true);

		// Add additional includes
		TArray<FString> Includes = { TEXT("GameplayEffectExtension.h") };
		if (!ReplicatedProps.IsEmpty())
		{
			Includes.Add(TEXT("Net/UnrealNetwork.h"));
		}

		FormatIncludeDirectives(Includes, RawItemString, RichTextString);

		// Add new line
		RawItemString += TEXT("\n");
		RichTextString += TEXT("\n");

		// normalize to platform newlines
		GBA::String::ToHostLineEndingsInline(RawItemString);
		GBA::String::ToHostLineEndingsInline(RichTextString);
	}
}

void FGBASourceViewIncludesListItem::FormatIncludeDirective(const FString& InIncludePath, FString& OutRawString, FString& OutRichString)
{
	// Add the comment to the raw string representation
	OutRawString = FString::Printf(TEXT("#include \"%s\""), *InIncludePath);

	// Mark the comment for rich text representation
	OutRichString = FString::Printf(
		TEXT("<%s>#include</> <%s>\"%s\"</>"),
		*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
		*GBA::HeaderViewSyntaxDecorators::CommentDecorator,
		*InIncludePath
	);
}

void FGBASourceViewIncludesListItem::FormatIncludeDirectives(const TArray<FString>& InIncludePaths, FString& OutRawString, FString& OutRichString)
{
	TArray<FString> RawStrings;
	TArray<FString> RichStrings;

	RawStrings.Reserve(InIncludePaths.Num());
	RichStrings.Reserve(InIncludePaths.Num());

	for (const FString& IncludePath : InIncludePaths)
	{
		FString RawString;
		FString RichString;
		FormatIncludeDirective(IncludePath, RawString, RichString);

		RawStrings.Add(RawString);
		RichStrings.Add(RichString);
	}
	
	// Add new line
	OutRawString += TEXT("\n\n");
	OutRichString += TEXT("\n\n");

	// Build the list
	OutRawString += FString::Join(RawStrings, TEXT("\n"));
	OutRichString += FString::Join(RichStrings, TEXT("\n"));
}

#undef LOCTEXT_NAMESPACE
