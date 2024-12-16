// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataTableEditorUtils.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STableRow.h"

class SGBANewDataTableWindowContent;

/**
 * A widget to represent a row in a Data Table Editor widget. This widget allows us to do things like right-click
 * and take actions on a particular row of a Data Table.
 */
class SGBADataTableListViewRow : public SMultiColumnTableRow<FDataTableEditorRowListViewDataPtr>
{
public:
	SLATE_BEGIN_ARGS(SGBADataTableListViewRow)
			: _IsEditable(false)
		{
		}

		/** The owning object. This allows us access to the actual data table being edited as well as some other API functions. */
		SLATE_ARGUMENT(TSharedPtr<SGBANewDataTableWindowContent>, HostWidget)

		/** The row we're working with to allow us to get naming information. */
		SLATE_ARGUMENT(FDataTableEditorRowListViewDataPtr, RowDataPtr)
		SLATE_ARGUMENT(bool, IsEditable)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);

	//~ Begin SMultiColumnTableRow interface
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;
	//~ End SMultiColumnTableRow interface
private:
	TSharedPtr<FName> CurrentName;
	FDataTableEditorRowListViewDataPtr RowDataPtr;
	TWeakPtr<SGBANewDataTableWindowContent> HostWidget;

	static FText GetCellText(const FDataTableEditorRowListViewDataPtr InRowDataPointer, const int32 ColumnIndex);
};
