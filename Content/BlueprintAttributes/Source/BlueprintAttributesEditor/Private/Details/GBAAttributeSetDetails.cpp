// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAAttributeSetDetails.h"

#include "AttributeSet.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "EdGraphSchema_K2.h"
#include "GBAEditorLog.h"
#include "Details/Slate/SGBANewAttributeVariableWidget.h"
#include "Details/Slate/SGBAPositiveActionButton.h"
#include "Editor/GBABlueprintEditor.h"
#include "Engine/Blueprint.h"
#include "Slate/GBANewAttributeViewModel.h"
#include "Styling/GBAAppStyle.h"
#include "Utils/GBAEditorUtils.h"

#define LOCTEXT_NAMESPACE "FGBAAttributeSetDetails"

TSharedRef<IDetailCustomization> FGBAAttributeSetDetails::MakeInstance()
{
	return MakeShared<FGBAAttributeSetDetails>();
}

void FGBAAttributeSetDetails::CustomizeDetails(IDetailLayoutBuilder& InDetailLayout)
{
	AttributeBeingCustomized = UE::GBA::EditorUtils::GetAttributeBeingCustomized(InDetailLayout);
	if (!AttributeBeingCustomized.IsValid())
	{
		return;
	}

	BlueprintBeingCustomized = UE::GBA::EditorUtils::GetBlueprintFromClass(AttributeBeingCustomized->GetClass());
	if (!BlueprintBeingCustomized.IsValid())
	{
		return;
	}

	BlueprintEditorPtr = UE::GBA::EditorUtils::FindBlueprintEditorForAsset(BlueprintBeingCustomized.Get());
	if (!BlueprintEditorPtr.IsValid())
	{
		return;
	}

	IDetailCategoryBuilder& Category = InDetailLayout.EditCategory("Default", LOCTEXT("DefaultsCategory", "Variables"));
	Category.RestoreExpansionState(false);

	const TSharedRef<SHorizontalBox> HeaderContentWidget = SNew(SHorizontalBox);
	HeaderContentWidget->AddSlot()
	[
		SNew(SHorizontalBox)
	];

	HeaderContentWidget->AddSlot()
	.AutoWidth()
	.VAlign(VAlign_Center)
	[
		SNew(SGBAPositiveActionButton)
		.ToolTipText(LOCTEXT("NewInputPoseTooltip", "Create a new Attribute"))
		.Icon(FGBAAppStyle::GetBrush("Icons.Plus"))
		.Text(LOCTEXT("AddNewLabel", "Add Attribute"))
		.OnGetMenuContent(this, &FGBAAttributeSetDetails::CreateNewAttributeVariableWidget)
	];
	Category.HeaderContent(HeaderContentWidget);
}

TSharedRef<SWidget> FGBAAttributeSetDetails::CreateNewAttributeVariableWidget()
{
	TSharedRef<FGBANewAttributeViewModel> ViewModel = MakeShared<FGBANewAttributeViewModel>();
	ViewModel->SetCustomizedBlueprint(BlueprintBeingCustomized);

	FEdGraphPinType PinType;
	PinType.PinCategory = UEdGraphSchema_K2::PC_Struct;
	PinType.PinSubCategory = NAME_None;
	PinType.PinSubCategoryObject = FGameplayAttributeData::StaticStruct();

	// Init from last saved variable states
	if (const TSharedPtr<FGBABlueprintEditor> BlueprintEditor = BlueprintEditorPtr.Pin()) 
	{
		ViewModel->SetVariableName(BlueprintEditor->GetLastUsedVariableName());
		ViewModel->SetbIsReplicated(BlueprintEditor->GetLastReplicatedState());
		if (BlueprintEditor->GetLastPinSubCategoryObject().IsValid())
		{
			PinType.PinSubCategoryObject = BlueprintEditor->GetLastPinSubCategoryObject();
		}
	}
	ViewModel->SetPinType(PinType);

	return SNew(SGBANewAttributeVariableWidget, ViewModel)
		.OnCancel_Static(&FGBAAttributeSetDetails::HandleAttributeWindowCancel)
		.OnFinish(this, &FGBAAttributeSetDetails::HandleAttributeWindowFinish);
}

void FGBAAttributeSetDetails::HandleAttributeWindowCancel(const TSharedPtr<FGBANewAttributeViewModel>& InViewModel)
{
	check(InViewModel.IsValid());
	GBA_EDITOR_LOG(Verbose, TEXT("Cancel -> %s"), *InViewModel->ToString())
}

void FGBAAttributeSetDetails::HandleAttributeWindowFinish(const TSharedPtr<FGBANewAttributeViewModel>& InViewModel) const
{
	check(InViewModel.IsValid());
	GBA_EDITOR_LOG(Verbose, TEXT("Finish -> %s"), *InViewModel->ToString())

	if (!BlueprintBeingCustomized.IsValid())
	{
		GBA_EDITOR_LOG(Error, TEXT("Failed to add new variable to blueprint because BlueprintBeingCustomized is null"))
		return;
	}

	if (const TSharedPtr<FGBABlueprintEditor> BlueprintEditor = BlueprintEditorPtr.Pin()) 
	{
		BlueprintEditor->SetLastPinSubCategoryObject(InViewModel->GetPinType().PinSubCategoryObject);
		BlueprintEditor->SetLastReplicatedState(InViewModel->GetbIsReplicated());
	}

	SGBANewAttributeVariableWidget::AddMemberVariable(
		BlueprintBeingCustomized.Get(),
		InViewModel->GetVariableName(),
		InViewModel->GetPinType(),
		InViewModel->GetDescription(),
		InViewModel->GetbIsReplicated()
	);
}

#undef LOCTEXT_NAMESPACE
