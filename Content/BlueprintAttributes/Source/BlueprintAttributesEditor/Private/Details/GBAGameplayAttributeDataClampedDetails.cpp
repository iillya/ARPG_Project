// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAGameplayAttributeDataClampedDetails.h"

#include "AttributeSet.h"
#include "DetailWidgetRow.h"
#include "GBAEditorLog.h"
#include "IDetailChildrenBuilder.h"
#include "Abilities/GBAAttributeSetBlueprintBase.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "GBAGameplayAttributeDataDetails"

FGBAGameplayAttributeDataClampedDetails::FGBAGameplayAttributeDataClampedDetails()
{
	GBA_EDITOR_LOG(VeryVerbose, TEXT("Construct FGBAGameplayAttributeDataClampedDetails ..."))
}

FGBAGameplayAttributeDataClampedDetails::~FGBAGameplayAttributeDataClampedDetails()
{
	GBA_EDITOR_LOG(VeryVerbose, TEXT("Destroyed FGBAGameplayAttributeDataClampedDetails ..."))
}

TSharedRef<IPropertyTypeCustomization> FGBAGameplayAttributeDataClampedDetails::MakeInstance()
{
	TSharedRef<FGBAGameplayAttributeDataClampedDetails> Details = MakeShared<FGBAGameplayAttributeDataClampedDetails>();
	Details->Initialize();
	return Details;
}

void FGBAGameplayAttributeDataClampedDetails::CustomizeHeader(const TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils)
{
	GBA_EDITOR_LOG(VeryVerbose, TEXT("FGBAGameplayAttributeDataClampedDetails::CustomizeHeader ..."))
	InitializeFromStructHandle(InStructPropertyHandle, InStructCustomizationUtils);

	const FGameplayAttributeData* AttributeData = GetGameplayAttributeData();
	check(AttributeData);

	InHeaderRow.
		NameContent()
		[
			InStructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(500)
		.MaxDesiredWidth(4096)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			.Padding(0.f, 0.f, 2.f, 0.f)
			[
				SNew(STextBlock)
				.Text(this, &FGBAGameplayAttributeDataClampedDetails::GetHeaderBaseValueText)
			]
		];
}

void FGBAGameplayAttributeDataClampedDetails::CustomizeChildren(const TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils)
{
	GBA_EDITOR_LOG(VeryVerbose, TEXT("FGBAGameplayAttributeDataClampedDetails::CustomizeChildren ..."))
	InitializeFromStructHandle(InStructPropertyHandle, InStructCustomizationUtils);
	
	CustomizeBaseValueChildren(InStructPropertyHandle, InStructBuilder, InStructCustomizationUtils, false);
	CustomizeCurrentValueChildren(InStructPropertyHandle, InStructBuilder, InStructCustomizationUtils);

	if (!InStructPropertyHandle->IsValidHandle())
	{
		return;
	}

	const TSharedPtr<IPropertyHandle> MinValueHandle = InStructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGBAGameplayClampedAttributeData, MinValue));
	if (MinValueHandle.IsValid())
	{
		IDetailPropertyRow& Row = InStructBuilder.AddProperty(MinValueHandle.ToSharedRef());
		Row.ShouldAutoExpand(true);
	}
	
	const TSharedPtr<IPropertyHandle> MaxValueHandle = InStructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FGBAGameplayClampedAttributeData, MaxValue));
	if (MaxValueHandle.IsValid())
	{
		IDetailPropertyRow& Row = InStructBuilder.AddProperty(MaxValueHandle.ToSharedRef());
		Row.ShouldAutoExpand(true);
	}
}

#undef LOCTEXT_NAMESPACE
