// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "SGBADataTableListViewRow.h"

#include "SGBANewDataTableWindowContent.h"
#include "SlateOptMacros.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SGBADataTableListViewRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
{
	RowDataPtr = InArgs._RowDataPtr;
	CurrentName = MakeShared<FName>(RowDataPtr->RowId);
	HostWidget = InArgs._HostWidget;

	SMultiColumnTableRow::Construct(
		FSuperRowType::FArguments()
		.Style(FAppStyle::Get(), "DataTableEditor.CellListViewRow"),
		InOwnerTableView
	);

	SetBorderImage(TAttribute<const FSlateBrush*>(this, &SGBADataTableListViewRow::GetBorder));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<SWidget> SGBADataTableListViewRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	const TSharedPtr<SGBANewDataTableWindowContent> HostWidgetPtr = HostWidget.Pin();
	TArray<FDataTableEditorColumnHeaderDataPtr>& AvailableColumns = HostWidgetPtr->AvailableColumns;

	const FName RowNumberColumnId("RowNumber");
	if (InColumnName.IsEqual(RowNumberColumnId))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SNew(STextBlock)
					.TextStyle(FAppStyle::Get(), "DataTableEditor.CellText")
					.Text(FText::FromString(FString::FromInt(RowDataPtr->RowNum)))
			];
	}

	const FName RowNameColumnId("RowName");
	if (InColumnName.IsEqual(RowNameColumnId))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SNew(STextBlock)
				.Text(RowDataPtr->DisplayName)
			];
	}

	int32 ColumnIndex = 0;
	for (; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
	{
		const FDataTableEditorColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];
		if (ColumnData->ColumnId == InColumnName)
		{
			break;
		}
	}

	// Valid column ID?
	if (AvailableColumns.IsValidIndex(ColumnIndex) && RowDataPtr->CellData.IsValidIndex(ColumnIndex))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SNew(STextBlock)
					.TextStyle(FAppStyle::Get(), "DataTableEditor.CellText")
					.Text_Static(&SGBADataTableListViewRow::GetCellText, RowDataPtr, ColumnIndex)
			];
	}


	return SNullWidget::NullWidget;
}

FText SGBADataTableListViewRow::GetCellText(const FDataTableEditorRowListViewDataPtr InRowDataPointer, const int32 ColumnIndex)
{
	if (InRowDataPointer.IsValid() && ColumnIndex < InRowDataPointer->CellData.Num())
	{
		return InRowDataPointer->CellData[ColumnIndex];
	}

	return FText::GetEmpty();
}
