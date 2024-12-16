// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAHeaderViewAttributeAccessorsListItem.h"

#include "LineEndings/GBALineEndings.h"

#define LOCTEXT_NAMESPACE "FGBAHeaderViewAttributesAccessorsListItem"

void FGBAHeaderViewAttributesAccessorsListItem::ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset)
{
}

FGBAHeaderViewAttributesAccessorsListItem::FGBAHeaderViewAttributesAccessorsListItem()
{
	FormatSingleLineCommentString(TEXT("Attribute accessors macros from AttributeSet.h"), RawItemString, RichTextString);

	// Add new line
	RawItemString += TEXT("\n");
	RichTextString += TEXT("\n");

	// Add macros
	{
		RawItemString += FString::Printf(TEXT("#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \\"));
		RichTextString += FString::Printf(
			TEXT("<%s>#define</> <%s>ATTRIBUTE_ACCESSORS</>(ClassName, PropertyName) \\"),
			*GBA::HeaderViewSyntaxDecorators::KeywordDecorator,
			*GBA::HeaderViewSyntaxDecorators::MacroDecorator
		);

		RawItemString += TEXT("\n");
		RichTextString += TEXT("\n");

		RawItemString += FString::Printf(TEXT("\tGAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \\"));
		RichTextString += FString::Printf(
			TEXT("\t<%s>GAMEPLAYATTRIBUTE_PROPERTY_GETTER</>(ClassName, PropertyName) \\"),
			*GBA::HeaderViewSyntaxDecorators::MacroDecorator
		);

		RawItemString += TEXT("\n");
		RichTextString += TEXT("\n");

		RawItemString += FString::Printf(TEXT("\tGAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \\"));
		RichTextString += FString::Printf(
			TEXT("\t<%s>GAMEPLAYATTRIBUTE_VALUE_GETTER</>(PropertyName) \\"),
			*GBA::HeaderViewSyntaxDecorators::MacroDecorator
		);

		RawItemString += TEXT("\n");
		RichTextString += TEXT("\n");

		RawItemString += FString::Printf(TEXT("\tGAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \\"));
		RichTextString += FString::Printf(
			TEXT("\t<%s>GAMEPLAYATTRIBUTE_VALUE_SETTER</>(PropertyName) \\"),
			*GBA::HeaderViewSyntaxDecorators::MacroDecorator
		);

		RawItemString += TEXT("\n");
		RichTextString += TEXT("\n");

		RawItemString += FString::Printf(TEXT("\tGAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)"));
		RichTextString += FString::Printf(
			TEXT("\t<%s>GAMEPLAYATTRIBUTE_VALUE_INITTER</>(PropertyName)"),
			*GBA::HeaderViewSyntaxDecorators::MacroDecorator
		);
	}

	// Add new line
	RawItemString += TEXT("\n");
	RichTextString += TEXT("\n");

	// normalize to platform newlines
	GBA::String::ToHostLineEndingsInline(RawItemString);
	GBA::String::ToHostLineEndingsInline(RichTextString);
}

FGBAHeaderViewListItemPtr FGBAHeaderViewAttributesAccessorsListItem::Create()
{
	return MakeShared<FGBAHeaderViewAttributesAccessorsListItem>();
}

#undef LOCTEXT_NAMESPACE
