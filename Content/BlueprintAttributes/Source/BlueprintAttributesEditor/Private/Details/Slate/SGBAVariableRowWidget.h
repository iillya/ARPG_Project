// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * Row widget wrapping a name and content widget for display in a form like view
 */
class SGBAVariableRowWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGBAVariableRowWidget)
		: _EditableTextHeight(26.f)
		, _VAlign(VAlign_Center)
		, _HAlign(HAlign_Left)
		, _NamePadding(FMargin(0.f, 3.f))
		, _ValuePadding(FMargin(0.f, 3.f))
		, _NameMaxWidth(80.f)
	{}

	SLATE_DEFAULT_SLOT(FArguments, NameContent)
	SLATE_NAMED_SLOT(FArguments, ValueContent)

	SLATE_ARGUMENT(float, EditableTextHeight)
	SLATE_ATTRIBUTE(float, FillWidth)
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)
	SLATE_ARGUMENT(EHorizontalAlignment, HAlign)
	SLATE_ARGUMENT(FMargin, NamePadding)
	SLATE_ARGUMENT(FMargin, ValuePadding)
	SLATE_ATTRIBUTE(float, NameMaxWidth)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	// void Construct(const FArguments& InArgs, const TSharedPtr<SWidget>& InNameContent, const TSharedPtr<SWidget>& InValueContent);
	void Construct(const FArguments& InArgs);
};
