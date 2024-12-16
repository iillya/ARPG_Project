// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"
#include "Misc/NotifyHook.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SWidget.h"
#include "Widgets/Views/SListView.h"

class FGBAAttributeSetWizardViewModel;
class FUICommandList;
class ITableRow;
class SComboButton;
class STableViewBase;
class SWidgetSwitcher;
class UBlueprint;
class UEdGraph;
class UStruct;
class UUserDefinedStruct;

enum class EGBAPreviewCppType : uint8;

class SGBAHeaderView : public SCompoundWidget, public FNotifyHook
{
public:
	SLATE_BEGIN_ARGS(SGBAHeaderView) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FAssetData& InAssetData, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);
	virtual ~SGBAHeaderView() override;

	//~ SWidget interface
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	//~ End SWidget interface

	//~ FNotifyHook interface
	/** Handles when the settings have changed, saves to config */
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;
	//~ End FNotifyHook interface

	/** Callback for class picker menu selecting a blueprint asset */
	void OnAssetSelected(const FAssetData& SelectedAsset);

	/** Returns the raw content for header file */
	FString GetHeaderContent() const;

	/** Returns the rich content for header file */
	FString GetHeaderRichContent() const;

	/** Returns the raw content for source file */
	FString GetSourceContent() const;

	/** Returns the rich content for header file */
	FString GetSourceRichContent() const;

private:
	/** View model for our widget (passed down from container widget) */
	TSharedPtr<FGBAAttributeSetWizardViewModel> ViewModel;

	/** List of UI Commands for this scope */
	TSharedPtr<FUICommandList> CommandList;

	/** Reference to the Class Picker combo button widget */
	TSharedPtr<SComboButton> ClassPickerComboButton;

	/** Reference to the HeaderListView Widget */
	TSharedPtr<SListView<FGBAHeaderViewListItemPtr>> HeaderListView;

	/** List Items source */
	TArray<FGBAHeaderViewListItemPtr> HeaderListItems;

	/** Reference to the HeaderListView Widget */
	TSharedPtr<SListView<FGBAHeaderViewListItemPtr>> SourceListView;

	/** List Items source */
	TArray<FGBAHeaderViewListItemPtr> SourceListItems;

	/** Switcher for active tab view */
	TSharedPtr<SWidgetSwitcher> TabContentSwitcher;

	/** Handler for a model property change */
	void HandleModelPropertyChanged(const FString& InPropertyName);
	
	/** Handler for segmented control tab view changed */
	void HandlePreviewValueChanged(EGBAPreviewCppType InActiveTab) const;
	
	/** Gets the text for the class picker combo button */
	FText GetClassPickerText() const;

	/** Constructs a Blueprint Class picker menu widget */
	TSharedRef<SWidget> GetClassPickerMenuContent();

	/** Constructs a DetailsView widget for the settings menu */
	TSharedRef<SWidget> GetSettingsMenuContent();

	/** Generates a row for a given List Item */
	TSharedRef<ITableRow> GenerateRowForItem(FGBAHeaderViewListItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable) const;

	/** Clears the list and repopulates it with info for the selected Blueprint */
	void RepopulateListView();
	void RepopulateHeaderListView();
	void RepopulateSourceListView();

	/** Adds items to the list view representing all functions present in the given blueprint */
	void PopulateFunctionItems(const UBlueprint* Blueprint);

	/** Gathers all function graphs from the blueprint and sorts them according to the selected method from config */
	void GatherFunctionGraphs(const UBlueprint* Blueprint, TArray<const UEdGraph*>& OutFunctionGraphs) const;

	/** Adds items to the list view representing all on rep functions to add based on attribute variables present */
	void PopulateHeaderOnRepFunctionItems(const UBlueprint* Blueprint, const TArray<const FProperty*> InReplicatedProps);

	/** Adds items to the list view representing all variables present in the given asset */
	void PopulateHeaderVariableItems(const UStruct* Struct);
	void AddHeaderVariableItems(TArray<const FProperty*> VarProperties);

	/** Adds line items for onrep notifier function implementations */
	void AddSourceOnRepFunctionItems(const TArray<const FProperty*>& InReplicatedProps);

	/** Creates a context menu for the list view */
	TSharedPtr<SWidget> OnPreviewContextMenuOpening(EGBAPreviewCppType InPreviewType) const;

	/** Called when a List Item is double clicked */
	void OnItemDoubleClicked(FGBAHeaderViewListItemPtr Item) const;

	/** Callback for when the selected asset is modified */
	void OnBlueprintChanged(UBlueprint* InBlueprint);

	/** UI Command Functions */
	void OnCopy() const;
	bool CanCopy() const;
	void OnSelectAll() const;
	FReply BrowseToAssetClicked() const;
	FReply OpenAssetEditorClicked() const;

	/** Returns the text to display for this button "Required Module Dependencies" with the number of dependencies in parentheses */
	FText GetRequiredModuleDependenciesText() const;
	
	/** Returns the list of required module dependencies as a tooltip text */
	FText GetRequiredModuleDependenciesTooltipText() const;

	/** Button click handler for RequiredModuleDependencies */
	FReply HandleRequiredModuleDependenciesClicked() const;
	
	/** Adjusts color for RequiredModuleDependencies button based on module validation */
	FSlateColor GetRequiredModuleDependenciesIconColor() const;
	
	/** Adjusts icon for RequiredModuleDependencies button based on module validation */
	const FSlateBrush* GetRequiredModuleDependenciesIcon() const;
};
