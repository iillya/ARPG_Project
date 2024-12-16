// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"

class UBlueprint;
class FMenuBuilder;
class SWidget;
enum class EValidatorResult;

/** rich text decorators for BlueprintHeaderView Syntax Highlighting */
namespace GBA::HeaderViewSyntaxDecorators
{
	extern const FString CommentDecorator;
	extern const FString ErrorDecorator;
	extern const FString IdentifierDecorator;
	extern const FString KeywordDecorator;
	extern const FString MacroDecorator;
	extern const FString TypenameDecorator;
	extern const FString StringLiteral;
	extern const FString NumericLiteral;
}

/** A base class for List Items in the Header View */
struct FGBAHeaderViewListItem : public TSharedFromThis<FGBAHeaderViewListItem>
{
	virtual ~FGBAHeaderViewListItem() {};

	/** Creates the widget for this list item */
	TSharedRef<SWidget> GenerateWidgetForItem() const;

	/** Creates a basic list item containing some text */
	static TSharedPtr<FGBAHeaderViewListItem> Create(FString InRawString, FString InRichText);

	/** Returns the raw item text for copy actions */
	const FString& GetRawItemString() const { return RawItemString; }
	
	/** Returns the rich item text */
	const FString& GetRichItemString() const { return RichTextString; }

	/** Allows the item to add items to the context menu if it is the only item selected */
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) {}

	/** Called when this List Item is double clicked */
	virtual void OnMouseButtonDoubleClick(TWeakObjectPtr<UObject> InAsset) {};

	/**
	 * Returns all FProperties from the passed in object (generally a Blueprint skeleton class)
	 *
	 * @param InStruct Owning UStruct
	 * @param bInFilterReplicated Whether to return only properties that are marked as replicated (Either Replicated or using RepNotify)
	 */
	static TArray<const FProperty*> GetAllProperties(const UStruct* InStruct, const bool bInFilterReplicated = false);

	/** Returns whether passed in owning UStruct has properties of type Clamped Attributes (hence needing the include) */
	static bool IsUsingClampedAttributeData(const UStruct* InStruct);
	
protected:
	/** A rich text representation of the item, including syntax highlighting and errors */
	FString RichTextString;

	/** A raw string representation of the item, used for copying the item */
	FString RawItemString;

	/** Validation Error text for when a new name is not a valid C++ Identifier */
	static const FText InvalidCPPIdentifierErrorText;
	
	/** Empty base constructor hidden from public */
	FGBAHeaderViewListItem() {};

	FGBAHeaderViewListItem(FString&& InRawString, FString&& InRichText);

	/** Returns classname prefixed */
	static FString GetClassNameToGenerate(const UBlueprint* InBlueprint, const FString& InDesiredClassName, const bool bIncludePrefix = true);

	/** 
	 * Formats a string into a C++ comment
	 * 
	 * @param InComment The string to format as a C++ comment
	 * @param OutRawString The string formatted as a C++ comment
	 * @param OutRichString The string formatted as a C++ comment with rich text decorators for syntax highlighting
	 */
	static void FormatCommentString(FString InComment, FString& OutRawString, FString& OutRichString);
	
	/** 
	 * Formats a string into a C++ comment
	 * 
	 * @param InComment The string to format as a C++ comment
	 * @param OutRawString The string formatted as a C++ comment
	 * @param OutRichString The string formatted as a C++ comment with rich text decorators for syntax highlighting
	 */
	static void FormatSingleLineCommentString(FString InComment, FString& OutRawString, FString& OutRichString);

	/** 
	 * returns a string representing the full C++ typename for the given property, 
	 * including template params for container types
	 */
	static FString GetCPPTypenameForProperty(const FProperty* InProperty, bool bIsMemberProperty = false);

	/** Checks whether a string is a valid C++ identifier */
	static bool IsValidCPPIdentifier(const FString& InIdentifier);

	/** Returns the correct Error text for a Validator Result */
	static const FText& GetErrorTextFromValidatorResult(EValidatorResult Result);
	
	/** Sorts an array of properties to optimize for minimal C++ struct padding */
	static void SortPropertiesForPadding(TArray<const FProperty*>& InOutProperties);

	/** Gets the typed property, returns nullptr if not cast. */
	template <typename PropertyType>
	const PropertyType* GetProperty(const FProperty* InProperty) const
	{
		static_assert(TIsDerivedFrom<PropertyType, FProperty>::Value, "PropertyType must derive from FProperty");
		return CastField<PropertyType>(InProperty);
	}

	/** Return String representation of the given FProperty */
	FString GetPropertyValue(const FProperty& InProperty, const UObject* InContainer, const FString& InDesiredClassName, const bool bInIsRichText = false) const;

	/** Returns whether the passed in cpp type should use const ref or not with OnRep definitions */
	static bool ShouldUseConstRef(const FString& InCPPType);
};

using FGBAHeaderViewListItemPtr = TSharedPtr<FGBAHeaderViewListItem>;

