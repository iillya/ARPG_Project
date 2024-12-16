// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "SGBAGameplayAttributeWidget.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Editor.h"
#include "GBAEditorLog.h"
#include "GBAEditorSettings.h"
#include "IGBAEditorModule.h"
#include "SlateOptMacros.h"
#include "Blueprint/GBAAttributeSetBlueprint.h"
#include "Misc/TextFilter.h"
#include "UObject/PropertyAccessUtil.h"
#include "UObject/UObjectIterator.h"
#include "UObject/UnrealType.h"
#include "Utils/GBAUtils.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STableViewBase.h"

#define LOCTEXT_NAMESPACE "K2Node"

DECLARE_DELEGATE_OneParam(FOnAttributePicked, FProperty*);

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

struct FGBAGameplayAttributeViewerNode
{
	FGBAGameplayAttributeViewerNode(const FProperty* InAttribute, const FString InAttributeName)
	{
		Attribute = InAttribute;
		AttributeName = MakeShareable(new FString(InAttributeName));
	}

	/** The displayed name for this node. */
	TSharedPtr<FString> AttributeName;

	TWeakFieldPtr<FProperty> Attribute;
};

/** The item used for visualizing the attribute in the list. */
class SGBAGameplayAttributeItem : public SComboRow<TSharedPtr<FGBAGameplayAttributeViewerNode>>
{
public:
	SLATE_BEGIN_ARGS(SGBAGameplayAttributeItem)
			: _TextColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))
		{
		}

		/** The text this item should highlight, if any. */
		SLATE_ARGUMENT(FText, HighlightText)
		/** The color text this item will use. */
		SLATE_ARGUMENT(FSlateColor, TextColor)
		/** The node this item is associated with. */
		SLATE_ARGUMENT(TSharedPtr<FGBAGameplayAttributeViewerNode>, AssociatedNode)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
	{
		AssociatedNode = InArgs._AssociatedNode;

		ChildSlot
		[
			SNew(SHorizontalBox)

			+SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.Padding(0.0f, 3.0f, 6.0f, 3.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(*AssociatedNode->AttributeName.Get()))
				.HighlightText(InArgs._HighlightText)
				.ColorAndOpacity(this, &SGBAGameplayAttributeItem::GetTextColor)
				.IsEnabled(true)
			]
		];

		TextColor = InArgs._TextColor;

		ConstructInternal(
			STableRow::FArguments()
			.ShowSelection(true),
			InOwnerTableView
		);
	}

	/** Returns the text color for the item based on if it is selected or not. */
	FSlateColor GetTextColor() const
	{
		const TSharedPtr<ITypedTableView<TSharedPtr<FGBAGameplayAttributeViewerNode>>> OwnerWidget = OwnerTablePtr.Pin();
		const TSharedPtr<FGBAGameplayAttributeViewerNode>* MyItem = OwnerWidget->Private_ItemFromWidget(this);
		const bool bIsSelected = OwnerWidget->Private_IsItemSelected(*MyItem);

		if (bIsSelected)
		{
			return FSlateColor::UseForeground();
		}

		return TextColor;
	}

private:
	/** The text color for this item. */
	FSlateColor TextColor;

	/** The Attribute Viewer Node this item is associated with. */
	TSharedPtr<FGBAGameplayAttributeViewerNode> AssociatedNode;
};

class SGBAGameplayAttributeListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGBAGameplayAttributeListWidget)
		: _FilterClass(nullptr)
		{}

		SLATE_ARGUMENT(FString, FilterMetaData)
		SLATE_ARGUMENT(const UClass*, FilterClass)
		SLATE_ARGUMENT(bool, ShowOnlyOwnedAttributes)
		SLATE_ARGUMENT(FOnAttributePicked, OnAttributePickedDelegate)

	SLATE_END_ARGS()

	/**
	* Construct the widget
	*
	* @param	InArgs			A declaration from which to construct the widget
	*/
	void Construct(const FArguments& InArgs);

	virtual ~SGBAGameplayAttributeListWidget() override;

private:
	typedef TTextFilter<const FProperty&> FAttributeTextFilter;

	/** Called by Slate when the filter box changes text. */
	void OnFilterTextChanged(const FText& InFilterText);

	/** Creates the row widget when called by Slate when an item appears on the list. */
	TSharedRef<ITableRow> OnGenerateRowForAttributeViewer(TSharedPtr<FGBAGameplayAttributeViewerNode> Item, const TSharedRef<STableViewBase>& OwnerTable) const;

	/** Called by Slate when an item is selected from the tree/list. */
	void OnAttributeSelectionChanged(TSharedPtr<FGBAGameplayAttributeViewerNode> Item, ESelectInfo::Type SelectInfo) const;

	/** Updates the list of items in the dropdown menu */
	TSharedPtr<FGBAGameplayAttributeViewerNode> UpdatePropertyOptions();

	/** Delegate to be called when an attribute is picked from the list */
	FOnAttributePicked OnAttributePicked;

	/** The search box */
	TSharedPtr<SSearchBox> SearchBoxPtr;

	/** Holds the Slate List widget which holds the attributes for the Attribute Viewer. */
	TSharedPtr<SListView<TSharedPtr<FGBAGameplayAttributeViewerNode>>> AttributeList;

	/** Array of items that can be selected in the dropdown menu */
	TArray<TSharedPtr<FGBAGameplayAttributeViewerNode>> PropertyOptions;

	/** Filters needed for filtering the assets */
	TSharedPtr<FAttributeTextFilter> AttributeTextFilter;

	/** Filter for meta data */
	FString FilterMetaData;
	
	/** Attribute set Class we want to see attributes of */
	TWeakObjectPtr<const UClass> FilterClass;
	
	/** Whether to filter the attribute list to only attributes owned by the containing class */
	bool bShowOnlyOwnedAttributes = false;
};

SGBAGameplayAttributeListWidget::~SGBAGameplayAttributeListWidget()
{
	if (OnAttributePicked.IsBound())
	{
		OnAttributePicked.Unbind();
	}
}

void SGBAGameplayAttributeListWidget::Construct(const FArguments& InArgs)
{
	struct FLocal
	{
		static void AttributeToStringArray(const FProperty& Property, OUT TArray<FString>& StringArray)
		{
			// UClass* Class = Property.GetOwnerClass();
			// if ((Class->IsChildOf(UAttributeSet::StaticClass()) && !Class->ClassGeneratedBy) ||
			// 	(Class->IsChildOf(UAbilitySystemComponent::StaticClass()) && !Class->ClassGeneratedBy))
			// {
			// 	StringArray.Add(FString::Printf(TEXT("%s.%s"), *Class->GetName(), *Property.GetName()));
			// }

			// GBA Changed ...
			const UClass* Class = Property.GetOwnerClass();
			if (Class->IsChildOf(UAttributeSet::StaticClass()) ||
				(Class->IsChildOf(UAbilitySystemComponent::StaticClass()) && !Class->ClassGeneratedBy))
			{
				StringArray.Add(FString::Printf(TEXT("%s.%s"), *Class->GetName(), *Property.GetName()));
			}
		}
	};

	FilterMetaData = InArgs._FilterMetaData;
	OnAttributePicked = InArgs._OnAttributePickedDelegate;
	FilterClass = InArgs._FilterClass;
	bShowOnlyOwnedAttributes = InArgs._ShowOnlyOwnedAttributes;

	// Setup text filtering
	AttributeTextFilter = MakeShared<FAttributeTextFilter>(FAttributeTextFilter::FItemToStringArray::CreateStatic(&FLocal::AttributeToStringArray));

	// Preload to ensure BP Attributes are loaded in memory so that they can be listed here
	IGBAEditorModule::Get().PreloadAssetsByClass(UGBAAttributeSetBlueprint::StaticClass());

	UpdatePropertyOptions();
	
	TSharedPtr<SWidget> ClassViewerContent;

	SAssignNew(ClassViewerContent, SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(SearchBoxPtr, SSearchBox)
			.HintText(NSLOCTEXT("Abilities", "SearchBoxHint", "Search Attributes (BP)"))
			.OnTextChanged(this, &SGBAGameplayAttributeListWidget::OnFilterTextChanged)
			.DelayChangeNotificationsWhileTyping(true)
		]

		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SSeparator)
			.Visibility(EVisibility::Collapsed)
		]

		+SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SAssignNew(AttributeList, SListView<TSharedPtr<FGBAGameplayAttributeViewerNode>>)
			.Visibility(EVisibility::Visible)
			.SelectionMode(ESelectionMode::Single)
			.ListItemsSource(&PropertyOptions)

 			// Generates the actual widget for a tree item
			.OnGenerateRow(this, &SGBAGameplayAttributeListWidget::OnGenerateRowForAttributeViewer)

 			// Find out when the user selects something in the tree
			.OnSelectionChanged(this, &SGBAGameplayAttributeListWidget::OnAttributeSelectionChanged)
		];


	ChildSlot
	[
		ClassViewerContent.ToSharedRef()
	];

	// Ensure we gain focus on search box when opening the combo box
	if (GEditor)
	{
		TWeakPtr<SGBAGameplayAttributeListWidget> LocalWeakThis = SharedThis(this);
		GEditor->GetTimerManager()->SetTimerForNextTick([LocalWeakThis]
		{
			if (const TSharedPtr<SGBAGameplayAttributeListWidget> StrongThis = LocalWeakThis.Pin(); StrongThis.IsValid())
			{
				FSlateApplication::Get().SetKeyboardFocus(StrongThis->SearchBoxPtr);
				FSlateApplication::Get().SetUserFocus(0, StrongThis->SearchBoxPtr);
			}
		});
	}
}

TSharedRef<ITableRow> SGBAGameplayAttributeListWidget::OnGenerateRowForAttributeViewer(const TSharedPtr<FGBAGameplayAttributeViewerNode> Item, const TSharedRef<STableViewBase>& OwnerTable) const
{
	TSharedRef<SGBAGameplayAttributeItem> ReturnRow = SNew(SGBAGameplayAttributeItem, OwnerTable)
		.HighlightText(SearchBoxPtr->GetText())
		.TextColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.f))
		.AssociatedNode(Item);

	return ReturnRow;
}

TSharedPtr<FGBAGameplayAttributeViewerNode> SGBAGameplayAttributeListWidget::UpdatePropertyOptions()
{
	PropertyOptions.Empty();
	TSharedPtr<FGBAGameplayAttributeViewerNode> InitiallySelected = MakeShared<FGBAGameplayAttributeViewerNode>(nullptr, TEXT("None"));

	PropertyOptions.Add(InitiallySelected);

	const UGBAEditorSettings& Settings = UGBAEditorSettings::Get();

	// Use IncludeSuper for iteration here only if bShowOnlyOwnedAttributed is used. To handle the use case of
	// FGBAGameplayClampedAttributeData defined in a native class (for instance after wizard generation), whose value
	// are tweaked in the details panel of a child Blueprint
	
	// EFieldIteratorFlags::SuperClassFlags IteratorFlag = EFieldIteratorFlags::ExcludeSuper;
	const EFieldIteratorFlags::SuperClassFlags IteratorFlag = bShowOnlyOwnedAttributes ? EFieldIteratorFlags::IncludeSuper : EFieldIteratorFlags::ExcludeSuper;

	// Gather all UAttribute classes
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		const UClass* Class = *ClassIt;

		// If we have been given a FilterClass, only show attributes of this AttributeSet class
		// (Way it's done right now, is containing details customization checks for ShowOnlyOwnedAttributed metadata on the
		// FGameplayAttribute property, and only passes down outer base class if metadata is present)
		if (FilterClass.IsValid() && !Class->IsChildOf(FilterClass.Get()))
		{
			continue;
		}
		
		if (FGBAUtils::IsValidAttributeClass(Class))
		{
			// Allow entire classes to be filtered globally
			if (Class->HasMetaData(TEXT("HideInDetailsView")))
			{
				continue;
			}

			for (TFieldIterator<FProperty> PropertyIt(Class, IteratorFlag); PropertyIt; ++PropertyIt)
			{
				FProperty* Property = *PropertyIt;

				// if we have a search string and this doesn't match, don't show it
				if (AttributeTextFilter.IsValid() && !AttributeTextFilter->PassesFilter(*Property))
				{
					continue;
				}

				// don't show attributes that are filtered by meta data
				if (!FilterMetaData.IsEmpty() && Property->HasMetaData(*FilterMetaData))
				{
					continue;
				}

				// Allow properties to be filtered globally (never show up)
				if (Property->HasMetaData(TEXT("HideInDetailsView")))
				{
					continue;
				}

				// Only allow field of expected types
				FString CPPType = Property->GetCPPType();
				if (!FGBAUtils::IsValidCPPType(CPPType))
				{
					continue;
				}

				const FString AttributeName = FString::Printf(TEXT("%s.%s"), *FGBAUtils::GetAttributeClassName(Class), *Property->GetName());

				// Allow properties to be filtered globally via Developer Settings (never show up)
				if (UGBAEditorSettings::IsAttributeFiltered(Settings.FilterAttributesList, AttributeName))
				{
					continue;
				}

				PropertyOptions.Add(MakeShared<FGBAGameplayAttributeViewerNode>(Property, AttributeName));
			}
		}

		// UAbilitySystemComponent can add 'system' attributes
		if (Class->IsChildOf(UAbilitySystemComponent::StaticClass()) && !Class->ClassGeneratedBy)
		{
			for (TFieldIterator<FProperty> PropertyIt(Class, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
			{
				FProperty* Property = *PropertyIt;

				// SystemAttributes have to be explicitly tagged
				if (Property->HasMetaData(TEXT("SystemGameplayAttribute")) == false)
				{
					continue;
				}

				// if we have a search string and this doesn't match, don't show it
				if (AttributeTextFilter.IsValid() && !AttributeTextFilter->PassesFilter(*Property))
				{
					continue;
				}

				const FString AttributeName = FString::Printf(TEXT("%s.%s"), *Class->GetName(), *Property->GetName());
				
				// Allow properties to be filtered globally via Developer Settings (never show up)
				if (UGBAEditorSettings::IsAttributeFiltered(Settings.FilterAttributesList, AttributeName))
				{
					continue;
				}

				PropertyOptions.Add(MakeShared<FGBAGameplayAttributeViewerNode>(Property, AttributeName));
			}
		}
	}

	return InitiallySelected;
}

void SGBAGameplayAttributeListWidget::OnFilterTextChanged(const FText& InFilterText)
{
	AttributeTextFilter->SetRawFilterText(InFilterText);
	SearchBoxPtr->SetError(AttributeTextFilter->GetFilterErrorText());

	UpdatePropertyOptions();
}

// ReSharper disable once CppParameterNeverUsed
void SGBAGameplayAttributeListWidget::OnAttributeSelectionChanged(const TSharedPtr<FGBAGameplayAttributeViewerNode> Item, ESelectInfo::Type SelectInfo) const
{
	OnAttributePicked.ExecuteIfBound(Item->Attribute.Get());
}

void SGBAGameplayAttributeWidget::Construct(const FArguments& InArgs)
{
	FilterMetaData = InArgs._FilterMetaData;
	OnAttributeChanged = InArgs._OnAttributeChanged;
	SelectedPropertyPtr = InArgs._DefaultProperty;
	FilterClass = InArgs._FilterClass;
	bShowOnlyOwnedAttributes = InArgs._ShowOnlyOwnedAttributes;
	
	// set up the combo button
	SAssignNew(ComboButton, SComboButton)
		.OnGetMenuContent(this, &SGBAGameplayAttributeWidget::GenerateAttributePicker)
		.ContentPadding(FMargin(2.0f, 2.0f))
		.ToolTipText(this, &SGBAGameplayAttributeWidget::GetSelectedValueAsString)
		.ButtonContent()
		[
			SNew(STextBlock)
			.Text(this, &SGBAGameplayAttributeWidget::GetSelectedValueAsString)
		];

	ChildSlot
	[
		ComboButton.ToSharedRef()
	];
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void SGBAGameplayAttributeWidget::OnAttributePicked(FProperty* InProperty)
{
	FProperty* Property = InProperty ? PropertyAccessUtil::FindPropertyByName(InProperty->GetFName(), InProperty->GetOwnerStruct()) : nullptr;

	if (OnAttributeChanged.IsBound())
	{
		OnAttributeChanged.Execute(Property ? Property : nullptr);
	}

	// Update the selected item for displaying
	SelectedPropertyPtr = Property ? Property : nullptr;

	// close the list
	ComboButton->SetIsOpen(false);
}

TSharedRef<SWidget> SGBAGameplayAttributeWidget::GenerateAttributePicker()
{
	return SNew(SBox)
		.WidthOverride(280)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			.MaxHeight(500)
			[
				SNew(SGBAGameplayAttributeListWidget)
				.OnAttributePickedDelegate(FOnAttributePicked::CreateSP(this, &SGBAGameplayAttributeWidget::OnAttributePicked))
				.FilterClass(FilterClass.Get())
				.ShowOnlyOwnedAttributes(bShowOnlyOwnedAttributes)
				.FilterMetaData(FilterMetaData)
			]
		];
}

FText SGBAGameplayAttributeWidget::GetSelectedValueAsString() const
{
	FText None = FText::FromString(TEXT("None"));
	
	// GBA_EDITOR_LOG(VeryVerbose, TEXT("SGBAGameplayAttributeWidget::GetSelectedValueAsString - SelectedProperty: %s"), *GetNameSafe(SelectedProperty))

	if (!SelectedPropertyPtr.IsValid())
	{
		// GBA_EDITOR_LOG(Warning, TEXT("Likely invalid property, SelectedProperty nullptr"))
		return None;
	}

	if (!SelectedPropertyPtr->IsValidLowLevel())
	{
		GBA_EDITOR_NS_LOG(Warning, TEXT("Likely invalid property, IsValidLowLevel returned false"))
		return None;
	}
	
	// Check for likely dirty property
	if (SelectedPropertyPtr->GetOffset_ForInternal() == 0)
	{
		GBA_EDITOR_NS_LOG(Warning, TEXT("Likely invalid property, offset 0"))
		return None;
	}

	const UClass* Class = SelectedPropertyPtr->GetOwnerClass();
	const FString PropertyName = SelectedPropertyPtr->GetDisplayNameText().ToString();
	const FString PropertyString = FString::Printf(TEXT("%s.%s"), *FGBAUtils::GetAttributeClassName(Class), *PropertyName);
	return FText::FromString(PropertyString);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
