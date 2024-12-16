// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Editor/GBABlueprintEditor.h"

#include "AttributeSet.h"
#include "EdGraphSchema_K2.h"
#include "GBADelegates.h"
#include "GBAEditorLog.h"
#include "IGBAEditorModule.h"
#include "IGBAScaffoldModule.h"
#include "Blueprint/GBAAttributeSetBlueprint.h"
#include "Details/Slate/GBANewAttributeViewModel.h"
#include "Details/Slate/SGBANewAttributeVariableWidget.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Styling/GBAEditorStyle.h"

#define LOCTEXT_NAMESPACE "GBABlueprintEditor"

FGBABlueprintEditor::FGBABlueprintEditor()
{
}

FGBABlueprintEditor::~FGBABlueprintEditor()
{
	if (AttributeWizardWindow.IsValid())
	{
		AttributeWizardWindow.Reset();
	}
}

void FGBABlueprintEditor::InitAttributeSetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, const TArray<UBlueprint*>& InBlueprints, const bool bShouldOpenInDefaultsMode)
{
	GBA_EDITOR_LOG(Verbose, TEXT("FGBABlueprintEditor::InitAttributeSetEditor"))
	InitBlueprintEditor(Mode, InitToolkitHost, InBlueprints, bShouldOpenInDefaultsMode);

	const TSharedPtr<FExtender> ToolbarExtender = MakeShared<FExtender>();
	ToolbarExtender->AddToolBarExtension(
		TEXT("Settings"),
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateSP(this, &FGBABlueprintEditor::FillToolbar)
	);

	AddToolbarExtender(ToolbarExtender);
	RegenerateMenusAndToolbars();

	if (InBlueprints.IsValidIndex(0))
	{
		if (UGBAAttributeSetBlueprint* Blueprint = Cast<UGBAAttributeSetBlueprint>(InBlueprints[0]))
		{
			Blueprint->RegisterDelegates();
		}
	}
}

void FGBABlueprintEditor::Compile()
{
	const UBlueprint* Blueprint = GetBlueprintObj();
	
	GBA_EDITOR_LOG(VeryVerbose, TEXT("FGBABlueprintEditor::Compile - PreCompile for %s"), *GetNameSafe(Blueprint))
	if (Blueprint)
	{
		if (const UPackage* Package = Blueprint->GetPackage())
		{
			FGBADelegates::OnPreCompile.Broadcast(Package->GetFName());
		}
	}
	
	FBlueprintEditor::Compile();
	GBA_EDITOR_LOG(VeryVerbose, TEXT("FGBABlueprintEditor::Compile - PostCompile for %s"), *GetNameSafe(Blueprint))

	// Bring toolkit back to front, cause UGBAEditorSubsystem will close any GE referencers and re-open
	// And the re-open will always focus the last Gameplay Effect BP, this focus window will happen after and make sure we don't loose focus
	// when we click the Compile button (but won't handle compile "in background" when hitting Play and some BP are automatically compiled by the editor)
	FocusWindow();
}

void FGBABlueprintEditor::InitToolMenuContext(FToolMenuContext& MenuContext)
{
	FBlueprintEditor::InitToolMenuContext(MenuContext);
}

FName FGBABlueprintEditor::GetToolkitFName() const
{
	return FName("GBABlueprintEditor");
}

FText FGBABlueprintEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AttributeSetEditorAppLabel", "Gameplay Attributes Editor");
}

FText FGBABlueprintEditor::GetToolkitToolTipText() const
{
	const UObject* EditingObject = GetEditingObject();

	check(EditingObject != nullptr);

	return GetToolTipTextForObject(EditingObject);
}

FString FGBABlueprintEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("BlueprintAttributeSetEditor");
}

FLinearColor FGBABlueprintEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FGBABlueprintEditor::GetDocumentationLink() const
{
	return FBlueprintEditor::GetDocumentationLink(); // todo: point this at the correct documentation
}

TWeakObjectPtr<UObject> FGBABlueprintEditor::GetLastPinSubCategoryObject() const
{
	return LastPinSubCategoryObject;
}

void FGBABlueprintEditor::SetLastPinSubCategoryObject(const TWeakObjectPtr<UObject>& InLastPinSubCategoryObject)
{
	LastPinSubCategoryObject = InLastPinSubCategoryObject;
}

bool FGBABlueprintEditor::GetLastReplicatedState() const
{
	return bLastReplicatedState;
}

void FGBABlueprintEditor::SetLastReplicatedState(const bool bInLastReplicatedState)
{
	bLastReplicatedState = bInLastReplicatedState;
}

FString FGBABlueprintEditor::GetLastUsedVariableName() const
{
	return LastUsedVariableName;
}

void FGBABlueprintEditor::SetLastUsedVariableName(const FString& InLastUsedVariableName)
{
	LastUsedVariableName = InLastUsedVariableName;
}

void FGBABlueprintEditor::FillToolbar(FToolBarBuilder& InToolbarBuilder)
{
	InToolbarBuilder.BeginSection(TEXT("BlueprintAttributes"));
	{
		InToolbarBuilder.AddComboButton(
			FUIAction(),
			FOnGetContent::CreateSP(this, &FGBABlueprintEditor::GenerateToolbarMenu),
			LOCTEXT("ToolbarAddLabel", "Add Attribute"),
			LOCTEXT("ToolbarAddToolTip", "Create a new Attribute"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Plus"),
			false
		);

		InToolbarBuilder.AddToolBarButton(
			FUIAction(FExecuteAction::CreateSP(this, &FGBABlueprintEditor::CreateDataTableWindow)),
			NAME_None,
			LOCTEXT("ToolbarGenerateDataTableLabel", "Create DataTable"),
			LOCTEXT("ToolbarGenerateDataTableTooltip", "Automatically generate a DataTable from this Blueprint Attributes properties"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.DataTable")
		);

		InToolbarBuilder.AddToolBarButton(
			FUIAction(FExecuteAction::CreateSP(this, &FGBABlueprintEditor::CreateAttributeWizard)),
			NAME_None,
			LOCTEXT("ToolbarGenerateCPPLabel", "Generate Equivalent C++"),
			LOCTEXT(
				"ToolbarGenerateCPPTooltip",
				"Provides a preview of what this class could look like in C++, "
				"and the ability to generate C++ header / source files from this Blueprint."
			),
			FSlateIcon(FGBAEditorStyle::Get().GetStyleSetName(), "Icons.HeaderView")
		);
	}
	InToolbarBuilder.EndSection();
}

TSharedRef<SWidget> FGBABlueprintEditor::GenerateToolbarMenu()
{
	FMenuBuilder MenuBuilder(true, nullptr);

	TSharedRef<FGBANewAttributeViewModel> ViewModel = MakeShared<FGBANewAttributeViewModel>();
	ViewModel->SetCustomizedBlueprint(GetBlueprintObj());
	ViewModel->SetVariableName(LastUsedVariableName);
	ViewModel->SetbIsReplicated(bLastReplicatedState);

	FEdGraphPinType PinType;
	PinType.PinCategory = UEdGraphSchema_K2::PC_Struct;
	PinType.PinSubCategory = NAME_None;
	PinType.PinSubCategoryObject = LastPinSubCategoryObject.IsValid() ? LastPinSubCategoryObject.Get() : FGameplayAttributeData::StaticStruct();
	ViewModel->SetPinType(PinType);

	TSharedRef<SGBANewAttributeVariableWidget> Widget = SNew(SGBANewAttributeVariableWidget, ViewModel)
		.OnCancel_Static(&FGBABlueprintEditor::HandleAttributeWindowCancel)
		.OnFinish(this, &FGBABlueprintEditor::HandleAttributeWindowFinish);

	MenuBuilder.AddWidget(Widget, FText::GetEmpty());
	return MenuBuilder.MakeWidget();
}

void FGBABlueprintEditor::HandleAttributeWindowCancel(const TSharedPtr<FGBANewAttributeViewModel>& InViewModel)
{
	check(InViewModel.IsValid());
}

void FGBABlueprintEditor::HandleAttributeWindowFinish(const TSharedPtr<FGBANewAttributeViewModel>& InViewModel)
{
	check(InViewModel.IsValid());

	LastPinSubCategoryObject = InViewModel->GetPinType().PinSubCategoryObject;
	bLastReplicatedState = InViewModel->GetbIsReplicated();
	LastUsedVariableName = InViewModel->GetVariableName();

	SGBANewAttributeVariableWidget::AddMemberVariable(
		GetBlueprintObj(),
		InViewModel->GetVariableName(),
		InViewModel->GetPinType(),
		InViewModel->GetDescription(),
		InViewModel->GetbIsReplicated()
	);
}

void FGBABlueprintEditor::CreateAttributeWizard()
{
	const FGBAAttributeWindowArgs WindowArgs;
	const FAssetData AssetData(GetBlueprintObj());
	if (!AttributeWizardWindow.IsValid())
	{
		AttributeWizardWindow = IGBAScaffoldModule::Get().CreateAttributeWizard(AssetData, WindowArgs);
		AttributeWizardWindow->SetOnWindowClosed(FOnWindowClosed::CreateSP(this, &FGBABlueprintEditor::HandleAttributeWizardClosed));
	}
	else
	{
		AttributeWizardWindow->BringToFront();
	}
}

// ReSharper disable once CppParameterNeverUsed
void FGBABlueprintEditor::HandleAttributeWizardClosed(const TSharedRef<SWindow>& InWindow)
{
	if (AttributeWizardWindow.IsValid())
	{
		AttributeWizardWindow.Reset();
	}
}

void FGBABlueprintEditor::CreateDataTableWindow()
{
	if (!DataTableWindow.IsValid())
	{
		const FGBADataTableWindowArgs WindowArgs;
		DataTableWindow = IGBAEditorModule::Get().CreateDataTableWindow(GetBlueprintObj(), WindowArgs);
		DataTableWindow->SetOnWindowClosed(FOnWindowClosed::CreateSP(this, &FGBABlueprintEditor::HandleDataTableWindowClosed));
	}
	else
	{
		DataTableWindow->BringToFront();
	}
}

// ReSharper disable once CppParameterNeverUsed
void FGBABlueprintEditor::HandleDataTableWindowClosed(const TSharedRef<SWindow>& InWindow)
{
	if (DataTableWindow.IsValid())
	{
		DataTableWindow.Reset();
	}
}

#undef LOCTEXT_NAMESPACE
