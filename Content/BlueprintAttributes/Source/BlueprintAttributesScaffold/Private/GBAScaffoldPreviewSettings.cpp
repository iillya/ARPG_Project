// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAScaffoldPreviewSettings.h"
#include "GBAScaffoldModule.h"

FGBAPreviewSyntaxColors::FGBAPreviewSyntaxColors()
	: Comment(0.107023f, 0.124772f, 0.162029f)
	, Error(0.904661f, 0.06301f, 0.06301f)
	, Macro(0.14996f, 0.300544f, 0.83077f)
	, Typename(0.783538f, 0.527115f, 0.198069f)
	, Identifier(0.745404f, 0.14996f, 0.177888f)
	, Keyword(0.564712f, 0.187821f, 0.723055f)
	, String(0.258183f, 0.539479f, 0.068478f)
	, Numeric(0.637597f, 0.323143f, 0.132868f)
{
}

UGBAScaffoldPreviewSettings::UGBAScaffoldPreviewSettings()
{
	
}

FName UGBAScaffoldPreviewSettings::GetCategoryName() const
{
	return PluginCategoryName;
}

FText UGBAScaffoldPreviewSettings::GetSectionText() const
{
	return NSLOCTEXT("ScaffoldPreviewSettings", "SectionText", "Scaffold Preview Settings");
}

void UGBAScaffoldPreviewSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (!PropertyChangedEvent.MemberProperty)
	{
		return;
	}

	const FName PropertyChangedName = PropertyChangedEvent.MemberProperty->GetFName();

	if (PropertyChangedName == GET_MEMBER_NAME_CHECKED(UGBAScaffoldPreviewSettings, FontSize))
	{
		FGBAScaffoldModule::HeaderViewTextStyle.SetFontSize(FontSize);
	}

	if (PropertyChangedName == GET_MEMBER_NAME_CHECKED(UGBAScaffoldPreviewSettings, SelectionColor))
	{
		FGBAScaffoldModule::HeaderViewTableRowStyle.ActiveBrush.TintColor = SelectionColor;
		FGBAScaffoldModule::HeaderViewTableRowStyle.ActiveHoveredBrush.TintColor = SelectionColor;
	}
}
