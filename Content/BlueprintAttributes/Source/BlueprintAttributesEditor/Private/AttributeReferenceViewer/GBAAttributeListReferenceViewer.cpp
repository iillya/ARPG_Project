// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "AttributeReferenceViewer/GBAAttributeListReferenceViewer.h"

#include "AbilitySystemComponent.h"
#include "Editor.h"
#include "GBAEditorLog.h"
#include "GBAEditorSettings.h"
#include "IGBAEditorModule.h"
#include "Blueprint/GBAAttributeSetBlueprint.h"
#include "Misc/EngineVersionComparison.h"
#include "UObject/UObjectIterator.h"
#include "Utils/GBAUtils.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSearchBox.h"

#if UE_VERSION_NEWER_THAN(5, 2, -1)
#include "AssetRegistry/AssetIdentifier.h"
#else
#include "AssetRegistry/AssetData.h"
#endif

#define LOCTEXT_NAMESPACE "GBAAttributeListReferenceViewer"

/** The item used for visualizing the attribute in the list. */
class SGBAAttributeListReferenceViewerItem : public SComboRow<TSharedPtr<FGBAAttributeListReferenceViewerNode>>
{
public:
	SLATE_BEGIN_ARGS(SGBAAttributeListReferenceViewerItem)
			: _TextColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))
		{
		}

		/** The text this item should highlight, if any. */
		SLATE_ARGUMENT(FText, HighlightText)
		/** The color text this item will use. */
		SLATE_ARGUMENT(FSlateColor, TextColor)
		/** The node this item is associated with. */
		SLATE_ARGUMENT(TSharedPtr<FGBAAttributeListReferenceViewerNode>, AssociatedNode)

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
				.ColorAndOpacity(this, &SGBAAttributeListReferenceViewerItem::GetTextColor)
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
		const TSharedPtr<ITypedTableView<TSharedPtr<FGBAAttributeListReferenceViewerNode>>> OwnerWidget = OwnerTablePtr.Pin();
		const TSharedPtr<FGBAAttributeListReferenceViewerNode>* MyItem = OwnerWidget->Private_ItemFromWidget(this);
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
	TSharedPtr<FGBAAttributeListReferenceViewerNode> AssociatedNode;
};

void SGBAAttributeListReferenceViewer::Construct(const FArguments& InArgs)
{
	struct FLocal
	{
		static void AttributeToStringArray(const FProperty& Property, OUT TArray<FString>& StringArray)
		{
			// GBA Changed ...
			const UClass* Class = Property.GetOwnerClass();
			if (Class->IsChildOf(UAttributeSet::StaticClass()) ||
				(Class->IsChildOf(UAbilitySystemComponent::StaticClass()) && !Class->ClassGeneratedBy))
			{
				StringArray.Add(FString::Printf(TEXT("%s.%s"), *Class->GetName(), *Property.GetName()));
			}
		}
	};
	
	// Setup text filtering
	AttributeTextFilter = MakeShared<FAttributeTextFilter>(FAttributeTextFilter::FItemToStringArray::CreateStatic(&FLocal::AttributeToStringArray));
	
	// Preload to ensure BP Attributes are loaded in memory so that they can be listed here
	IGBAEditorModule::Get().PreloadAssetsByClass(UGBAAttributeSetBlueprint::StaticClass());
	
	UpdatePropertyOptions();
	
	TWeakPtr<SGBAAttributeListReferenceViewer> WeakSelf = StaticCastWeakPtr<SGBAAttributeListReferenceViewer>(AsWeak());

	const TSharedRef<SWidget> Picker = 
		SNew(SBorder)
		.Padding(InArgs._Padding)
		.BorderImage(FStyleDefaults::GetNoBrush())
		[
			SNew(SVerticalBox)

			// Gameplay Tag Tree controls
			+SVerticalBox::Slot()
			.AutoHeight()
			.VAlign(VAlign_Top)
			[
				SNew(SHorizontalBox)

				// Search
				+SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.FillWidth(1.f)
				.Padding(0,1,5,1)
				[
					SAssignNew(SearchAttributeBox, SSearchBox)
					.HintText(LOCTEXT("GameplayTagPicker_SearchBoxHint", "Search Gameplay Attributes"))
					.OnTextChanged(this, &SGBAAttributeListReferenceViewer::OnFilterTextChanged)
					.DelayChangeNotificationsWhileTyping(true)
				]
			]

			// Gameplay Tags tree
			+SVerticalBox::Slot()
			.FillHeight(1)
			[
				SAssignNew(AttributesContainerWidget, SBorder)
				.BorderImage(FStyleDefaults::GetNoBrush())
				[
					SAssignNew(AttributeList, SListView<TSharedPtr<FGBAAttributeListReferenceViewerNode>>)
					.Visibility(EVisibility::Visible)
					.SelectionMode(ESelectionMode::Single)
					.ListItemsSource(&PropertyOptions)

					// Generates the actual widget for a tree item
					.OnGenerateRow(this, &SGBAAttributeListReferenceViewer::OnGenerateRowForAttributeViewer)

					// Find out when the user selects something in the tree
					.OnSelectionChanged(this, &SGBAAttributeListReferenceViewer::OnAttributeSelectionChanged)
				]
			]
		];
	
	ChildSlot
	[
		// Populate the widget
		Picker
	];
}

void SGBAAttributeListReferenceViewer::OnFilterTextChanged(const FText& InFilterText)
{
	AttributeTextFilter->SetRawFilterText(InFilterText);
	SearchAttributeBox->SetError(AttributeTextFilter->GetFilterErrorText());

	UpdatePropertyOptions();

	AttributeList->RequestListRefresh();
}

TSharedPtr<SWidget> SGBAAttributeListReferenceViewer::GetWidgetToFocusOnOpen()
{
	return SearchAttributeBox;
}

void SGBAAttributeListReferenceViewer::UpdatePropertyOptions()
{
	PropertyOptions.Empty();

	const UGBAEditorSettings& Settings = UGBAEditorSettings::Get();

	// Gather all UAttribute classes
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		const UClass* Class = *ClassIt;

		if (FGBAUtils::IsValidAttributeClass(Class))
		{
			// Allow entire classes to be filtered globally
			if (Class->HasMetaData(TEXT("HideInDetailsView")))
			{
				continue;
			}

			for (TFieldIterator<FProperty> PropertyIt(Class, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
			{
				FProperty* Property = *PropertyIt;

				// if we have a search string and this doesn't match, don't show it
				if (AttributeTextFilter.IsValid() && !AttributeTextFilter->PassesFilter(*Property))
				{
					GBA_EDITOR_NS_LOG(Warning, TEXT("%s filtered"), *Property->GetName());
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

				PropertyOptions.Add(MakeShared<FGBAAttributeListReferenceViewerNode>(Property, AttributeName));
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

				PropertyOptions.Add(MakeShared<FGBAAttributeListReferenceViewerNode>(Property, AttributeName));
			}
		}
	}
}

TSharedRef<ITableRow> SGBAAttributeListReferenceViewer::OnGenerateRowForAttributeViewer(TSharedPtr<FGBAAttributeListReferenceViewerNode> InItem, const TSharedRef<STableViewBase>& InOwnerTable) const
{
	TSharedRef<SGBAAttributeListReferenceViewerItem> ReturnRow = SNew(SGBAAttributeListReferenceViewerItem, InOwnerTable)
		.HighlightText(SearchAttributeBox->GetText())
		.TextColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.f))
		.AssociatedNode(InItem);

	return ReturnRow;
}

void SGBAAttributeListReferenceViewer::OnAttributeSelectionChanged(TSharedPtr<FGBAAttributeListReferenceViewerNode> InItem, ESelectInfo::Type SelectInfo) const
{
	if (InItem.IsValid() && InItem->Attribute.IsValid())
	{
		TArray<FAssetIdentifier> AssetIdentifiers;
		const FName Name = FName(*FString::Printf(TEXT("%s.%s"), *InItem->Attribute->GetOwnerVariant().GetName(), *InItem->Attribute->GetName()));
		AssetIdentifiers.Add(FAssetIdentifier(FGameplayAttribute::StaticStruct(), Name));
		FEditorDelegates::OnOpenReferenceViewer.Broadcast(AssetIdentifiers, FReferenceViewerParams());	
	}
}

#undef LOCTEXT_NAMESPACE
