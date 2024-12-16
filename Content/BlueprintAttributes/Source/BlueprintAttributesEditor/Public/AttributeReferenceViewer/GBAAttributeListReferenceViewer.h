// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/TextFilter.h"
#include "UObject/WeakFieldPtr.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class SBorder;
class SSearchBox;

struct FGBAAttributeListReferenceViewerNode
{
	FGBAAttributeListReferenceViewerNode(const FProperty* InAttribute, const FString& InAttributeName)
	{
		Attribute = InAttribute;
		AttributeName = MakeShareable(new FString(InAttributeName));
	}

	/** The displayed name for this node. */
	TSharedPtr<FString> AttributeName;

	TWeakFieldPtr<FProperty> Attribute;
};

/** Widget allowing user to list Gameplay Attributes and open up the reference viewer for them */
class BLUEPRINTATTRIBUTESEDITOR_API SGBAAttributeListReferenceViewer : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGBAAttributeListReferenceViewer)
		: _Padding(FMargin(2.0f))
	{}

		// Padding inside the picker widget
		SLATE_ARGUMENT(FMargin, Padding)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	/** Updates the tag list when the filter text changes */
	void OnFilterTextChanged(const FText& InFilterText);
	
	/** Gets the widget to focus once the menu opens. */
	TSharedPtr<SWidget> GetWidgetToFocusOnOpen();
	
private:
	typedef TTextFilter<const FProperty&> FAttributeTextFilter;
	
	/** Allows for the user to find a specific gameplay attribute in the list */
	TSharedPtr<SSearchBox> SearchAttributeBox;

	/** Filters needed for filtering the attributes */
	TSharedPtr<FAttributeTextFilter> AttributeTextFilter;
	
	/** Container widget holding the attribute list */
	TSharedPtr<SBorder> AttributesContainerWidget;
	
	/** Holds the Slate List widget that holds the attributes for the Attribute Viewer. */
	TSharedPtr<SListView<TSharedPtr<FGBAAttributeListReferenceViewerNode>>> AttributeList;
	
	/** Array of items that can be selected in the dropdown menu */
	TArray<TSharedPtr<FGBAAttributeListReferenceViewerNode>> PropertyOptions;
	
	/** Updates the list of items in the dropdown menu */
	void UpdatePropertyOptions();
	
	/** Creates the row widget when called by Slate when an item appears on the list. */
	TSharedRef<ITableRow> OnGenerateRowForAttributeViewer(TSharedPtr<FGBAAttributeListReferenceViewerNode> InItem, const TSharedRef<STableViewBase>& InOwnerTable) const;
	
	/** Called when an item is selected from the list. */
	void OnAttributeSelectionChanged(TSharedPtr<FGBAAttributeListReferenceViewerNode> InItem, ESelectInfo::Type SelectInfo) const;
};
