// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataTableEditorUtils.h"
#include "ViewModel/IGBASlateViewModel.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class ITableRow;
class SEditableTextBox;
class SHeaderRow;
class SPathPicker;
class STableViewBase;
class STextBlock;
class SWarningOrErrorBox;
class SWidgetSwitcher;

class FNewDataTableWindowViewModel : public IGBASlateViewModel
{
	DECLARE_VIEWMODEL_PROPERTY(FString, SelectedPath)
	DECLARE_VIEWMODEL_PROPERTY(FString, AssetName)
	FNewDataTableWindowViewModel() = default;

	virtual void Initialize() override
	{
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("SelectedPath: %s, AssetName: %s"), *SelectedPath, *AssetName);
	}
};

/**
 * Widget to provide an UI to choose a content browser path to generate a new DataTable (FAttributeMetaData) based on the properties
 * of a given Attribute Set Blueprint.
 */
class SGBANewDataTableWindowContent : public SCompoundWidget
{
	friend class SGBADataTableListViewRow;

public:
	SLATE_BEGIN_ARGS(SGBANewDataTableWindowContent)
		{
		}

	SLATE_END_ARGS()

	/** The column id for the row number list view column */
	static const FName RowNumberColumnId;

	/** The column id for the row name list view column */
	static const FName RowNameColumnId;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TWeakObjectPtr<UBlueprint>& InBlueprint);
	virtual ~SGBANewDataTableWindowContent() override;

	static FString GenerateCSVFromBlueprintAttributes(const TWeakObjectPtr<UBlueprint>& InBlueprint);

private:
	/** Weak pointer to the UBlueprint we're basing the model / widget on */
	TWeakObjectPtr<UBlueprint> Blueprint;

	/** View model for this widget */
	TSharedPtr<FNewDataTableWindowViewModel> ViewModel;

	/** Path Picker used by the dialog */
	TSharedPtr<SPathPicker> PathPicker;

	/** The path box. */
	TSharedPtr<STextBlock> PathText;

	/** The name box. Only used in save dialogs. */
	TSharedPtr<SEditableTextBox> NameEditableText;

	/** Widget switcher to display either warn or error box */
	TSharedPtr<SWidgetSwitcher> WarningOrErrorSwitcher;

	/** Error box widget */
	TSharedPtr<SWarningOrErrorBox> ErrorBox;

	/** Error box widget */
	TSharedPtr<SWarningOrErrorBox> WarningBox;

	/** List view responsible for showing the rows in VisibleRows for each entry in AvailableColumns */
	TSharedPtr<SListView<FDataTableEditorRowListViewDataPtr>> CellsListView;

	/** Header row containing entries for each column in AvailableColumns */
	TSharedPtr<SHeaderRow> ColumnNamesHeaderRow;

	/** Array of the columns that are available for editing */
	TArray<FDataTableEditorColumnHeaderDataPtr> AvailableColumns;

	/** Array of the rows that are available for editing */
	TArray<FDataTableEditorRowListViewDataPtr> AvailableRows;

	/** Width of the row name column */
	float RowNameColumnWidth = 0.f;

	/** Width of the row number column */
	float RowNumberColumnWidth = 0.f;

	/** The error text from the last validity check */
	FText LastInputValidityErrorText;

	/** True if the last validity check returned that the class name/path is valid for creation */
	bool bLastInputValidityCheckSuccessful = true;
	bool bLastInputValidityWarningSuccessful = true;

	void HandleBlueprintChanged(UBlueprint* InBlueprint);
	void HandleModelPropertyChanged(const FString& InPropertyChanged);
	void UpdateInputValidity();
	void SetError(const FText& InErrorText);
	void SetWarning(const FText& InWarningText);

	/** Fills up AvailableColumns / AvailableRows and builds up ColumnNamesHeaderRow columns, computing widths in the process */
	void BuildDataColumnsAndRows(const UDataTable* InDataTable);

	/** Make the widget for a row entry in the data table row list view */
	TSharedRef<ITableRow> MakeRowWidget(FDataTableEditorRowListViewDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable);

	/** Updates view model whenever a new path is selected */
	void HandlePathSelected(const FString& InPath) const;

	/** Gets the visibility of the name error label */
	EVisibility GetNameErrorLabelVisibility() const;

	/** Gets the text to display in the name error label */
	FText GetNameErrorLabelText() const;

	/** Gets the visibility of the name warning label */
	EVisibility GetNameWarningLabelVisibility() const;

	/** Gets the text to display in the name warning label */
	FText GetNameWarningLabelText() const;

	/** Gets the name to display in the path text block */
	FText GetPathNameText() const;

	/** Gets the name to display in the asset name box */
	FText GetAssetNameText() const;

	/** Fired when the asset name box text is committed */
	void HandleAssetNameTextCommitted(const FText& InText, ETextCommit::Type InCommitType) const;

	/** Determines if the confirm button (e.g. Open/Save) is enabled. */
	bool IsConfirmButtonEnabled() const;

	/** Handler for when the confirm button (e.g. Open/Save) is clicked */
	FReply OnConfirmClicked();

	/** Handler for when the cancel button is clicked */
	FReply OnCancelClicked();

	/** Closes this dialog */
	void CloseDialog();

	void RefreshRowNameColumnWidth();
	void RefreshRowNumberColumnWidth();

	enum class ECalculateColumnType : uint8
	{
		RowNum,
		DisplayName
	};

	float CalculateColumnWidth(const float InInitialValue, const ECalculateColumnType InColumnType);

	FString GetObjectPathForSave(const bool bInIsLongPath = true) const;
};
