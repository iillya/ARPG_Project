// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAHeaderViewCopyrightListItem.h"

#include "GeneralProjectSettings.h"
#include "LineEndings/GBALineEndings.h"

#define LOCTEXT_NAMESPACE "FGBAHeaderViewCopyrightListItem"

void FGBAHeaderViewCopyrightListItem::ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset)
{
}

FGBAHeaderViewCopyrightListItem::FGBAHeaderViewCopyrightListItem()
{
	const FString CopyrightNotice = GetDefault<UGeneralProjectSettings>()->CopyrightNotice;
	if (CopyrightNotice.IsEmpty())
	{
		return;
	}

	// Format comment
	FormatSingleLineCommentString(CopyrightNotice, RawItemString, RichTextString);

	// Add new line
	RawItemString += TEXT("\n");
	RichTextString += TEXT("\n");

	// normalize to platform newlines
	GBA::String::ToHostLineEndingsInline(RawItemString);
	GBA::String::ToHostLineEndingsInline(RichTextString);
}

FGBAHeaderViewListItemPtr FGBAHeaderViewCopyrightListItem::Create()
{
	return MakeShared<FGBAHeaderViewCopyrightListItem>();
}

#undef LOCTEXT_NAMESPACE
