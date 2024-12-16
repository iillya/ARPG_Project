// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"

class FGBAAttributeSetWizardViewModel;

/** A header view list item that displays a list of include directives */
struct FGBAHeaderViewIncludesListItem : public FGBAHeaderViewListItem
{
	explicit FGBAHeaderViewIncludesListItem(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	/** Creates a list item for the Header view representing a declaration for the given blueprint */
	static FGBAHeaderViewListItemPtr Create(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface

	/** 
	 * Formats a string into a C++ include directive
	 * 
	 * @param InIncludePath The string to format as a C++ include directive
	 * @param OutRawString The string formatted as a C++ include directive
	 * @param OutRichString The string formatted as a C++ include directive with rich text decorators for syntax highlighting
	 */
	static void FormatIncludeDirective(const FString& InIncludePath, FString& OutRawString, FString& OutRichString);
	static void FormatIncludeDirectives(const TArray<FString>& InIncludePaths, FString& OutRawString, FString& OutRichString);
};
