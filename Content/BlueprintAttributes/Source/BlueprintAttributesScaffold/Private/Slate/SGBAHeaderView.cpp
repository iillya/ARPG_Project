// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "SGBAHeaderView.h"

#include "ContentBrowserModule.h"
#include "EdGraphSchema_K2.h"
#include "GBAScaffoldLog.h"
#include "GBAScaffoldModule.h"
#include "GBAScaffoldPreviewSettings.h"
#include "GBAScaffoldUtils.h"
#include "IContentBrowserSingleton.h"
#include "K2Node_FunctionEntry.h"
#include "PropertyEditorModule.h"
#include "SourceCodeNavigation.h"
#include "Blueprint/GBAAttributeSetBlueprint.h"
#include "Editor/EditorEngine.h"
#include "Framework/Commands/GenericCommands.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "HAL/PlatformApplicationMisc.h"
#include "HeaderView/GBAHeaderViewClassListItem.h"
#include "HeaderView/GBAHeaderViewFunctionListItem.h"
#include "HeaderView/GBAHeaderViewVariableListItem.h"
#include "HeaderView/Attributes/GBAHeaderViewAttributeAccessorsListItem.h"
#include "HeaderView/Attributes/GBAHeaderViewAttributeVariableListItem.h"
#include "HeaderView/Attributes/GBAHeaderViewCopyrightListItem.h"
#include "HeaderView/Attributes/GBAHeaderViewGetLifetimeListItem.h"
#include "HeaderView/Attributes/GBAHeaderViewIncludesListItem.h"
#include "HeaderView/Attributes/GBAHeaderViewOnRepListItem.h"
#include "LineEndings/GBALineEndings.h"
#include "Misc/EngineVersionComparison.h"
#include "Models/GBAAttributeSetWizardViewModel.h"
#include "SourceView/GBASourceViewGetLifetimeListItem.h"
#include "SourceView/GBASourceViewIncludesListItem.h"
#include "SourceView/GBASourceViewOnRepListItem.h"
#include "Styling/StyleColors.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Utils/GBAUtils.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/SSegmentedControl.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

#define LOCTEXT_NAMESPACE "SGBAHeaderView"

extern UNREALED_API UEditorEngine* GEditor;

// ReSharper disable once CppParameterNeverUsed
void SGBAHeaderView::Construct(const FArguments& InArgs, const FAssetData& InAssetData, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	ViewModel = InViewModel;
	check(ViewModel.IsValid())
	ViewModel->OnModelPropertyChanged().AddThreadSafeSP(this, &SGBAHeaderView::HandleModelPropertyChanged);
	
	CommandList = MakeShared<FUICommandList>();
	CommandList->MapAction(FGenericCommands::Get().Copy,
		FExecuteAction::CreateRaw(this, &SGBAHeaderView::OnCopy),
		FCanExecuteAction::CreateRaw(this, &SGBAHeaderView::CanCopy));
	CommandList->MapAction(FGenericCommands::Get().SelectAll,
		FExecuteAction::CreateRaw(this, &SGBAHeaderView::OnSelectAll));

	// Init Header View widget / source (so that we can call OnAssetSelected right after, which will cause a model update and refresh)
	HeaderListView = SNew(SListView<FGBAHeaderViewListItemPtr>)
		.ListItemsSource(&HeaderListItems)
		.OnGenerateRow(this, &SGBAHeaderView::GenerateRowForItem)
		.OnContextMenuOpening(this, &SGBAHeaderView::OnPreviewContextMenuOpening, EGBAPreviewCppType::Header)
		.OnMouseButtonDoubleClick(this, &SGBAHeaderView::OnItemDoubleClicked);

	// Init Header View widget / source (so that we can call OnAssetSelected right after, which will cause a model update and refresh)
	SourceListView = SNew(SListView<FGBAHeaderViewListItemPtr>)
		.ListItemsSource(&SourceListItems)
		.OnGenerateRow(this, &SGBAHeaderView::GenerateRowForItem)
		.OnContextMenuOpening(this, &SGBAHeaderView::OnPreviewContextMenuOpening, EGBAPreviewCppType::Source)
		.OnMouseButtonDoubleClick(this, &SGBAHeaderView::OnItemDoubleClicked);

	// Updates model with passed in asset data and update the selected blueprint, causing a re-render
	OnAssetSelected(InAssetData);

	constexpr float PaddingAmount = 8.0f;
	
	ChildSlot
	[
		SNew(SVerticalBox)
		
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FMargin(PaddingAmount))
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ClassPickerLabel", "Generate from Blueprint:"))
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SSpacer)
				.Size(FVector2D(PaddingAmount))
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SBox)
				.WidthOverride(400.0f)
				[
					SAssignNew(ClassPickerComboButton, SComboButton)
					.OnGetMenuContent(this, &SGBAHeaderView::GetClassPickerMenuContent)
					.ButtonContent()
					[
						SNew(STextBlock)
						.Text(this, &SGBAHeaderView::GetClassPickerText)
					]
				]
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
				.ToolTipText(LOCTEXT("BrowseToBlueprintTooltip", "Browse to Selected Blueprint in Content Browser"))
				.OnClicked(this, &SGBAHeaderView::BrowseToAssetClicked)
				.ContentPadding(4.0f)
				.Content()
				[
					SNew(SImage)
					.Image(FAppStyle::Get().GetBrush("Icons.BrowseContent"))
				]
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
				.ToolTipText(LOCTEXT("EditBlueprintTooltip", "Open Selected Blueprint in Blueprint Editor"))
				.OnClicked(this, &SGBAHeaderView::OpenAssetEditorClicked)
				.ContentPadding(4.0f)
				.Content()
				[
					SNew(SImage)
					.Image(FAppStyle::Get().GetBrush("Icons.Edit"))
				]
			]
			
			+SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			.Padding(FMargin(PaddingAmount * 1.5f, 0.f, PaddingAmount, 0.f))
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Preview", "Preview:"))
			]
			
			+SHorizontalBox::Slot()
			.FillWidth(1.f)
			.HAlign(HAlign_Left)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SSegmentedControl<EGBAPreviewCppType>)
					// .Value(CurrentPreviewValue)
					.Value(ViewModel->GetCurrentPreviewValue())
					.OnValueChanged(this, &SGBAHeaderView::HandlePreviewValueChanged)
					+SSegmentedControl<EGBAPreviewCppType>::Slot(EGBAPreviewCppType::Header)
					.Text(LOCTEXT("Header", "Header"))
					.ToolTip(LOCTEXT("HeaderTooltip", "Click to preview header file about to be generated"))
					+SSegmentedControl<EGBAPreviewCppType>::Slot(EGBAPreviewCppType::Source)
					.Text(LOCTEXT("Source", "Source"))
					.ToolTip(LOCTEXT("SourceTooltip", "Click to preview source file about to be generated"))
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(16.f, 0.f)
				[
					SNew(SButton)
					.ForegroundColor(FSlateColor::UseForeground())
					.ButtonStyle(FAppStyle::Get(), "SimpleButton")
					.OnClicked(this, &SGBAHeaderView::HandleRequiredModuleDependenciesClicked)
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						[
							SNew(SImage)
							.Image(this, &SGBAHeaderView::GetRequiredModuleDependenciesIcon)
							.ColorAndOpacity(this, &SGBAHeaderView::GetRequiredModuleDependenciesIconColor)
						]
						+SHorizontalBox::Slot()
						.Padding(FMargin(5, 0, 0, 0))
						.VAlign(VAlign_Center)
						.AutoWidth()
						[
							SNew(STextBlock)
							.TextStyle(FAppStyle::Get(), "NormalText")
							.Text(this, &SGBAHeaderView::GetRequiredModuleDependenciesText)
							.ToolTipText(this, &SGBAHeaderView::GetRequiredModuleDependenciesTooltipText)
							.ColorAndOpacity(FSlateColor::UseForeground())
						]
					]
				]
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			[
				SNew(SComboButton)
				.HasDownArrow(false)
				.ForegroundColor(FSlateColor::UseForeground())
				.ButtonStyle(FAppStyle::Get(), "SimpleButton")
				.OnGetMenuContent(this, &SGBAHeaderView::GetSettingsMenuContent)
				.ButtonContent()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Center)
					[
						SNew(SImage)
						.Image(FAppStyle::Get().GetBrush("Icons.Toolbar.Settings"))
						.ColorAndOpacity(FSlateColor::UseForeground())
					]
					+SHorizontalBox::Slot()
					.Padding(FMargin(5, 0, 0, 0))
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(STextBlock)
						.TextStyle(FAppStyle::Get(), "NormalText")
						.Text(LOCTEXT("SettingsLabel", "Settings"))
						.ColorAndOpacity(FSlateColor::UseForeground())
					]
				]
			]
		]
		
		+SVerticalBox::Slot()
		.Padding(FMargin(PaddingAmount))
		[
			SNew(SBorder)
			[
				SAssignNew(TabContentSwitcher, SWidgetSwitcher)
				.WidgetIndex(0)
				+SWidgetSwitcher::Slot()
				[
					HeaderListView.ToSharedRef()
				]
				+SWidgetSwitcher::Slot()
				[
					SourceListView.ToSharedRef()
				]
			]
		]
	];
}

SGBAHeaderView::~SGBAHeaderView()
{
	if (ViewModel.IsValid())
	{
		ViewModel->OnModelPropertyChanged().RemoveAll(this);

		if (ViewModel->GetSelectedBlueprint().IsValid())
		{
			UBlueprint* Blueprint = ViewModel->GetSelectedBlueprint().Get();
			Blueprint->OnChanged().RemoveAll(this);
		}
	}
}

FReply SGBAHeaderView::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (CommandList.IsValid() && CommandList->ProcessCommandBindings(InKeyEvent))
	{
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void SGBAHeaderView::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{
	UGBAScaffoldPreviewSettings* BlueprintHeaderViewSettings = GetMutableDefault<UGBAScaffoldPreviewSettings>();
	check(BlueprintHeaderViewSettings);
	BlueprintHeaderViewSettings->SaveConfig();

	// repopulate the list view to update text style/sorting method based on settings
	RepopulateListView();
}

// ReSharper disable once CppParameterNeverUsed
void SGBAHeaderView::HandleModelPropertyChanged(const FString& InPropertyName)
{
	RepopulateListView();
}

void SGBAHeaderView::HandlePreviewValueChanged(const EGBAPreviewCppType InActiveTab) const
{
	check(ViewModel.IsValid());
	ViewModel->SetCurrentPreviewValue(InActiveTab);

	if (InActiveTab == EGBAPreviewCppType::Header)
	{
		TabContentSwitcher->SetActiveWidgetIndex(0);
	}
	else if (InActiveTab == EGBAPreviewCppType::Source)
	{
		TabContentSwitcher->SetActiveWidgetIndex(1);
	}
}

FText SGBAHeaderView::GetClassPickerText() const
{
	check(ViewModel.IsValid());
	
	if (const UBlueprint* Blueprint = ViewModel->GetSelectedBlueprint().Get())
	{
		return FText::FromName(Blueprint->GetFName());
	}

	return LOCTEXT("ClassPickerPickClass", "Select Blueprint Class");
}

TSharedRef<SWidget> SGBAHeaderView::GetClassPickerMenuContent()
{
	const FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	FAssetPickerConfig AssetPickerConfig;
	AssetPickerConfig.SelectionMode = ESelectionMode::Single;
	AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateSP(this, &SGBAHeaderView::OnAssetSelected);
#if UE_VERSION_NEWER_THAN(5, 1, -1)
	AssetPickerConfig.Filter.ClassPaths.Add(UGBAAttributeSetBlueprint::StaticClass()->GetClassPathName());
#else
	AssetPickerConfig.Filter.ClassNames.Add(UGBAAttributeSetBlueprint::StaticClass()->GetFName());
#endif
	AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;
	AssetPickerConfig.SaveSettingsName = TEXT("HeaderPreviewClassPickerSettings");
	const TSharedRef<SWidget> AssetPickerWidget = ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig);

	return SNew(SBox)
		.HeightOverride(500.f)
		[
			AssetPickerWidget
		];
}

TSharedRef<SWidget> SGBAHeaderView::GetSettingsMenuContent()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");	
	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bShowPropertyMatrixButton = false;
		DetailsViewArgs.bShowOptions = false;
		DetailsViewArgs.NotifyHook = this;
	}
	TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(GetMutableDefault<UGBAScaffoldPreviewSettings>());
	return DetailsView;
}

void SGBAHeaderView::OnAssetSelected(const FAssetData& SelectedAsset)
{
	if (ClassPickerComboButton.IsValid())
	{
		ClassPickerComboButton->SetIsOpen(false);
	}
	
	check(ViewModel.IsValid())
	if (ViewModel->GetSelectedBlueprint().IsValid())
	{
		if (UBlueprint* OldBlueprint = ViewModel->GetSelectedBlueprint().Get())
		{
			OldBlueprint->OnChanged().RemoveAll(this);
			OldBlueprint->OnCompiled().RemoveAll(this);
		}
	}

	ViewModel->SetSelectedBlueprint(nullptr, false);

	if (UBlueprint* Blueprint = Cast<UBlueprint>(SelectedAsset.GetAsset()))
	{
		// Blueprint->OnCompiled().AddThreadSafeSP(this, &SGBAHeaderView::OnBlueprintChanged);
		Blueprint->OnChanged().AddThreadSafeSP(this, &SGBAHeaderView::OnBlueprintChanged);
		ViewModel->SetSelectedBlueprint(Blueprint);
	}

	RepopulateListView();
}

FString SGBAHeaderView::GetHeaderContent() const
{
	TArray<FString> LineItemsContent;
	Algo::Transform(HeaderListItems, LineItemsContent, [](const FGBAHeaderViewListItemPtr& Item)
	{
		return Item->GetRawItemString();
	});

	FString Content = FString::Join(LineItemsContent, TEXT("\n"));
	GBA::String::ToHostLineEndingsInline(Content);
	return Content;
}

FString SGBAHeaderView::GetHeaderRichContent() const
{
	TArray<FString> LineItemsContent;
	Algo::Transform(HeaderListItems, LineItemsContent, [](const FGBAHeaderViewListItemPtr& Item)
	{
		return Item->GetRichItemString();
	});

	FString Content = FString::Join(LineItemsContent, TEXT("\n"));
	GBA::String::ToHostLineEndingsInline(Content);
	return Content;
}

FString SGBAHeaderView::GetSourceContent() const
{
	TArray<FString> LineItemsContent;
	Algo::Transform(SourceListItems, LineItemsContent, [](const FGBAHeaderViewListItemPtr& Item)
	{
		return Item->GetRawItemString();
	});

	FString Content = FString::Join(LineItemsContent, TEXT("\n"));
	GBA::String::ToHostLineEndingsInline(Content);
	return Content;
}

FString SGBAHeaderView::GetSourceRichContent() const
{
	TArray<FString> LineItemsContent;
	Algo::Transform(SourceListItems, LineItemsContent, [](const FGBAHeaderViewListItemPtr& Item)
	{
		return Item->GetRichItemString();
	});

	FString Content = FString::Join(LineItemsContent, TEXT("\n"));
	GBA::String::ToHostLineEndingsInline(Content);
	return Content;
}

TSharedRef<ITableRow> SGBAHeaderView::GenerateRowForItem(const FGBAHeaderViewListItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable) const
{
	return SNew(STableRow<FGBAHeaderViewListItemPtr>, OwnerTable)
		.Style(&FGBAScaffoldModule::HeaderViewTableRowStyle)
		.Content()
		[
			Item->GenerateWidgetForItem()
		];
}

void SGBAHeaderView::RepopulateListView()
{
	if (HeaderListView.IsValid())
	{
		// Try to preserve user selection
		TArray<FGBAHeaderViewListItemPtr> SelectedItems = HeaderListView->GetSelectedItems();

		int32 Index = 0;
		TArray<int32> SelectionIndexes;

		for (const FGBAHeaderViewListItemPtr& Item : HeaderListItems)
		{
			if (HeaderListView->IsItemSelected(Item))
			{
				SelectionIndexes.Add(Index);
			}
			
			++Index;
		}

		RepopulateHeaderListView();
		
		for (const int32 SelectionIndex : SelectionIndexes)
		{
			if (!HeaderListItems.IsValidIndex(SelectionIndex))
			{
				continue;
			}

			const FGBAHeaderViewListItemPtr Item = HeaderListItems[SelectionIndex];
			HeaderListView->SetItemSelection(Item, true);
		}
	}

	if (SourceListView.IsValid())
	{
		// Try to preserve user selection
		TArray<FGBAHeaderViewListItemPtr> SelectedItems = SourceListView->GetSelectedItems();

		int32 Index = 0;
		TArray<int32> SelectionIndexes;

		for (const FGBAHeaderViewListItemPtr& Item : SourceListItems)
		{
			if (SourceListView->IsItemSelected(Item))
			{
				SelectionIndexes.Add(Index);
			}
			
			++Index;
		}

		RepopulateSourceListView();
		
		for (const int32 SelectionIndex : SelectionIndexes)
		{
			if (!SourceListItems.IsValidIndex(SelectionIndex))
			{
				continue;
			}

			const FGBAHeaderViewListItemPtr Item = SourceListItems[SelectionIndex];
			SourceListView->SetItemSelection(Item, true);
		}
	}
}

void SGBAHeaderView::RepopulateHeaderListView()
{
	HeaderListItems.Empty();

	check(ViewModel.IsValid());
	const TWeakObjectPtr<UBlueprint> BlueprintWeakPtr = ViewModel->GetSelectedBlueprint();

	if (const UBlueprint* Blueprint = BlueprintWeakPtr.Get())
	{
		// Add the copyright notice
		HeaderListItems.Add(FGBAHeaderViewCopyrightListItem::Create());

		// Add the include directives
		HeaderListItems.Add(FGBAHeaderViewIncludesListItem::Create(ViewModel));

		// Add the attribute accessors macro
		HeaderListItems.Add(FGBAHeaderViewAttributesAccessorsListItem::Create());
		
		// Add the class declaration
		HeaderListItems.Add(FGBAHeaderViewClassListItem::Create(ViewModel));

		PopulateHeaderVariableItems(Blueprint->GeneratedClass);
		// PopulateFunctionItems(Blueprint);

		// Add the GetLifetimeReplicatedProp
		const TArray<const FProperty*> ReplicatedProps = FGBAHeaderViewListItem::GetAllProperties(Blueprint->GeneratedClass, true);
		if (!ReplicatedProps.IsEmpty())
		{
			HeaderListItems.Add(FGBAHeaderViewGetLifetimeListItem::Create(ViewModel));
			PopulateHeaderOnRepFunctionItems(Blueprint, ReplicatedProps);
		}

		// Add the closing brace of the class
		HeaderListItems.Add(FGBAHeaderViewListItem::Create(TEXT("};"), TEXT("};")));
	}

	HeaderListView->RequestListRefresh();
}

void SGBAHeaderView::RepopulateSourceListView()
{
	SourceListItems.Empty();

	check(ViewModel.IsValid());

	// Add the copyright notice
	SourceListItems.Add(FGBAHeaderViewCopyrightListItem::Create());

	// Add the include directives
	SourceListItems.Add(FGBASourceViewIncludesListItem::Create(ViewModel));

	// Add the GetLifetimeReplicatedProp implementation
	const TWeakObjectPtr<UBlueprint> SelectedBlueprint = ViewModel->GetSelectedBlueprint();
	check(SelectedBlueprint.IsValid());
	
	const TArray<const FProperty*> ReplicatedProps = FGBAHeaderViewListItem::GetAllProperties(SelectedBlueprint->GeneratedClass, true);
	if (!ReplicatedProps.IsEmpty())
	{
		SourceListItems.Add(FGBASourceViewGetLifetimeListItem::Create(ViewModel));
	}
	AddSourceOnRepFunctionItems(ReplicatedProps);

	// PopulateSourceVariableItems(Blueprint->GeneratedClass);
	// PopulateFunctionItems(Blueprint);

	SourceListView->RequestListRefresh();
}

void SGBAHeaderView::PopulateFunctionItems(const UBlueprint* Blueprint)
{
	if (Blueprint)
	{
		TArray<const UEdGraph*> FunctionGraphs;
		GatherFunctionGraphs(Blueprint, FunctionGraphs);

		// We should only add an access specifier line if the previous function was a different one
		int32 PrevAccessSpecifier = 0;
		for (const UEdGraph* FunctionGraph : FunctionGraphs)
		{
			if (FunctionGraph && !UEdGraphSchema_K2::IsConstructionScript(FunctionGraph))
			{
				TArray<UK2Node_FunctionEntry*> EntryNodes;
				FunctionGraph->GetNodesOfClass<UK2Node_FunctionEntry>(EntryNodes);

				if (ensure(EntryNodes.Num() == 1 && EntryNodes[0]))
				{
					int32 AccessSpecifier = EntryNodes[0]->GetFunctionFlags() & FUNC_AccessSpecifiers;
					AccessSpecifier = AccessSpecifier ? AccessSpecifier : FUNC_Public; //< Blueprint OnRep functions don't have one of these flags set, default to public in this case and others like it

					if (AccessSpecifier != PrevAccessSpecifier)
					{
						switch (AccessSpecifier)
						{
						default: 
						case FUNC_Public:
							HeaderListItems.Add(FGBAHeaderViewListItem::Create(TEXT("public:"), FString::Printf(TEXT("<%s>public</>:"), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator)));
							break;
						case FUNC_Protected:
							HeaderListItems.Add(FGBAHeaderViewListItem::Create(TEXT("protected:"), FString::Printf(TEXT("<%s>protected</>:"), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator)));
							break;
						case FUNC_Private:
							HeaderListItems.Add(FGBAHeaderViewListItem::Create(TEXT("private:"), FString::Printf(TEXT("<%s>private</>:"), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator)));
							break;
						}
					}
					else
					{
						// add an empty line to space functions out
						HeaderListItems.Add(FGBAHeaderViewListItem::Create(TEXT(""), TEXT("")));
					}

					PrevAccessSpecifier = AccessSpecifier;

					HeaderListItems.Add(FGBAHeaderViewFunctionListItem::Create(EntryNodes[0]));
				}
			}
		}
	}
}

void SGBAHeaderView::GatherFunctionGraphs(const UBlueprint* Blueprint, TArray<const UEdGraph*>& OutFunctionGraphs) const
{
	for (const UEdGraph* FunctionGraph : Blueprint->FunctionGraphs)
	{
		OutFunctionGraphs.Add(FunctionGraph);
	}

	const UGBAScaffoldPreviewSettings* BlueprintHeaderViewSettings = GetDefault<UGBAScaffoldPreviewSettings>();
	if (BlueprintHeaderViewSettings->SortMethod == EGBAPreviewSortMethod::SortByAccessSpecifier)
	{
		OutFunctionGraphs.Sort([](const UEdGraph& LeftGraph, const UEdGraph& RightGraph)
			{
				TArray<UK2Node_FunctionEntry*> LeftEntryNodes;
				LeftGraph.GetNodesOfClass<UK2Node_FunctionEntry>(LeftEntryNodes);
				TArray<UK2Node_FunctionEntry*> RightEntryNodes;
				RightGraph.GetNodesOfClass<UK2Node_FunctionEntry>(RightEntryNodes);
				if (ensure(LeftEntryNodes.Num() == 1 && LeftEntryNodes[0] && RightEntryNodes.Num() == 1 && RightEntryNodes[0]))
				{
					const int32 LeftAccessSpecifier = LeftEntryNodes[0]->GetFunctionFlags() & FUNC_AccessSpecifiers;
					const int32 RightAccessSpecifier = RightEntryNodes[0]->GetFunctionFlags() & FUNC_AccessSpecifiers;

					return (LeftAccessSpecifier == FUNC_Public && RightAccessSpecifier != FUNC_Public) || (LeftAccessSpecifier == FUNC_Protected && RightAccessSpecifier == FUNC_Private);
				}

				return false;
			});
	}
}

void SGBAHeaderView::PopulateHeaderOnRepFunctionItems(const UBlueprint* Blueprint, const TArray<const FProperty*> InReplicatedProps)
{
	check(Blueprint);

	// Check if we have at least one item with repnotify to add a definition for, and prevent adding a protected access with no items
	bool bHasRepNotifies = false;
	for (const FProperty* VarProperty : InReplicatedProps)
	{
		if (VarProperty && VarProperty->HasAnyPropertyFlags(CPF_Net) && VarProperty->HasAnyPropertyFlags(CPF_RepNotify))
		{
			bHasRepNotifies = true;
			break;
		}

		if (FGBAUtils::IsValidCPPType(VarProperty->GetCPPType()))
		{
			bHasRepNotifies = true;
			break;
		}
	}

	if (bHasRepNotifies)
	{
		HeaderListItems.Add(FGBAHeaderViewListItem::Create(
			TEXT("protected:"),
			FString::Printf(TEXT("<%s>protected</>:"), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator)
		));
	}

	for (const FProperty* VarProperty : InReplicatedProps)
	{
		if (!VarProperty)
		{
			continue;
		}

		if (FGBAUtils::IsValidCPPType(VarProperty->GetCPPType()))
		{
			HeaderListItems.Add(FGBAHeaderViewOnRepListItem::Create(*VarProperty));
	
		}
		else if (VarProperty->HasAnyPropertyFlags(CPF_Net) && VarProperty->HasAnyPropertyFlags(CPF_RepNotify))
		{
			HeaderListItems.Add(FGBAHeaderViewOnRepListItem::Create(*VarProperty));
		}
	}
}

void SGBAHeaderView::AddHeaderVariableItems(TArray<const FProperty*> VarProperties)
{
	// We should only add an access specifier line if the previous variable was a different one
	int32 PrevAccessSpecifier = 0;
	for (const FProperty* VarProperty : VarProperties)
	{
		constexpr int32 Private = 2;
		constexpr int32 Public = 1;
		const int32 AccessSpecifier = VarProperty->GetBoolMetaData(FBlueprintMetadata::MD_Private) ? Private : Public;
		if (AccessSpecifier != PrevAccessSpecifier)
		{
			switch (AccessSpecifier)
			{
			case Public:
				HeaderListItems.Add(FGBAHeaderViewListItem::Create(TEXT("public:"), FString::Printf(TEXT("<%s>public</>:"), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator)));
				break;
			case Private:
				HeaderListItems.Add(FGBAHeaderViewListItem::Create(TEXT("private:"), FString::Printf(TEXT("<%s>private</>:"), *GBA::HeaderViewSyntaxDecorators::KeywordDecorator)));
				break;
			default:
				break;
			}

			PrevAccessSpecifier = AccessSpecifier;
		}
		else
		{
			// add an empty line to space variables out
			HeaderListItems.Add(FGBAHeaderViewListItem::Create(TEXT(""), TEXT("")));
		}

		FGBAHeaderViewListItemPtr VariableItem = FGBAUtils::IsValidCPPType(VarProperty->GetCPPType()) ?
			FGBAHeaderViewAttributeVariableListItem::Create(*VarProperty, ViewModel) :
			FGBAHeaderViewVariableListItem::Create(*VarProperty, ViewModel);
		
		HeaderListItems.Add(VariableItem);
	}
}

void SGBAHeaderView::AddSourceOnRepFunctionItems(const TArray<const FProperty*>& InReplicatedProps)
{
	// We should only add an access specifier line if the previous variable was a different one
	for (const FProperty* VarProperty : InReplicatedProps)
	{
		if (!VarProperty)
		{
			continue;
		}

		if (FGBAUtils::IsValidCPPType(VarProperty->GetCPPType()))
		{
			SourceListItems.Add(FGBASourceViewOnRepListItem::Create(ViewModel, *VarProperty));
		}
		else if (VarProperty->HasAnyPropertyFlags(CPF_Net) && VarProperty->HasAnyPropertyFlags(CPF_RepNotify))
		{
			SourceListItems.Add(FGBASourceViewOnRepListItem::Create(ViewModel, *VarProperty));
		}
	}
}

void SGBAHeaderView::PopulateHeaderVariableItems(const UStruct* Struct)
{
	const TArray<const FProperty*> VarProperties = FGBAHeaderViewListItem::GetAllProperties(Struct);
	AddHeaderVariableItems(VarProperties);
}

TSharedPtr<SWidget> SGBAHeaderView::OnPreviewContextMenuOpening(const EGBAPreviewCppType InPreviewType) const
{
	check(ViewModel.IsValid());
	
	FMenuBuilder MenuBuilder(true, CommandList);

	MenuBuilder.AddMenuEntry(FGenericCommands::Get().SelectAll);
	MenuBuilder.AddMenuEntry(FGenericCommands::Get().Copy);

	TArray<FGBAHeaderViewListItemPtr> SelectedListItems;

	if (InPreviewType == EGBAPreviewCppType::Header)
	{
		HeaderListView->GetSelectedItems(SelectedListItems);
	}
	else if (InPreviewType == EGBAPreviewCppType::Source)
	{
		SourceListView->GetSelectedItems(SelectedListItems);
	}
	
	if (SelectedListItems.Num() == 1 && ViewModel->GetSelectedBlueprint().IsValid())
	{
		SelectedListItems[0]->ExtendContextMenu(MenuBuilder, ViewModel->GetSelectedBlueprint().Get());
	}

	return MenuBuilder.MakeWidget();
}

void SGBAHeaderView::OnItemDoubleClicked(const FGBAHeaderViewListItemPtr Item) const
{
	check(ViewModel.IsValid());

	if (ViewModel->GetSelectedBlueprint().IsValid())
	{
		Item->OnMouseButtonDoubleClick(ViewModel->GetSelectedBlueprint().Get());
	}
}

// ReSharper disable once CppParameterNeverUsed
// ReSharper disable once CppParameterMayBeConstPtrOrRef
void SGBAHeaderView::OnBlueprintChanged(UBlueprint* InBlueprint)
{
	GBA_SCAFFOLD_LOG(Verbose, TEXT("SGBAHeaderView::OnBlueprintChanged - InBlueprint: %s"), *GetNameSafe(InBlueprint))
	if (GEditor)
	{
		TWeakPtr<SGBAHeaderView> LocalWeakThis = SharedThis(this);
		GEditor->GetTimerManager()->SetTimerForNextTick([LocalWeakThis]
		{
			if (const TSharedPtr<SGBAHeaderView> StrongThis = LocalWeakThis.Pin(); StrongThis.IsValid())
			{
				StrongThis->RepopulateListView();
			}
		});
	}
}

void SGBAHeaderView::OnCopy() const
{
	check(ViewModel.IsValid());
	const EGBAPreviewCppType CurrentPreviewValue = ViewModel->GetCurrentPreviewValue();
	
	const TSharedPtr<SListView<FGBAHeaderViewListItemPtr>> ListView = CurrentPreviewValue == EGBAPreviewCppType::Header ? HeaderListView : SourceListView;
	TArray<FGBAHeaderViewListItemPtr> ListItems = CurrentPreviewValue == EGBAPreviewCppType::Header ? HeaderListItems : SourceListItems;
	if (!ListView)
	{
		return;
	}
	
	constexpr int32 StringReserveSize = 2048;
	FString CopyText;
	CopyText.Reserve(StringReserveSize);
	for (const FGBAHeaderViewListItemPtr& Item : ListItems)
	{
		if (ListView->IsItemSelected(Item))
		{
			CopyText += Item->GetRawItemString() + LINE_TERMINATOR;
		}
	}

	FPlatformApplicationMisc::ClipboardCopy(*CopyText);
}

bool SGBAHeaderView::CanCopy() const
{
	check(ViewModel.IsValid());
	const EGBAPreviewCppType CurrentPreviewValue = ViewModel->GetCurrentPreviewValue();
	
	const TSharedPtr<SListView<FGBAHeaderViewListItemPtr>> ListView = CurrentPreviewValue == EGBAPreviewCppType::Header ? HeaderListView : SourceListView;
	if (!ListView)
	{
		return false;
	}
	
	return ListView->GetNumItemsSelected() > 0;
}

void SGBAHeaderView::OnSelectAll() const
{
	check(ViewModel.IsValid());
	const EGBAPreviewCppType CurrentPreviewValue = ViewModel->GetCurrentPreviewValue();
	
	const TSharedPtr<SListView<FGBAHeaderViewListItemPtr>> ListView = CurrentPreviewValue == EGBAPreviewCppType::Header ? HeaderListView : SourceListView;
	if (!ListView)
	{
		return;
	}
	
	ListView->SetItemSelection(HeaderListItems, true);
}

FReply SGBAHeaderView::BrowseToAssetClicked() const
{
	check(ViewModel.IsValid());

	TArray<FAssetData> AssetsToSync;
	if (UBlueprint* Blueprint = ViewModel->GetSelectedBlueprint().Get())
	{
		AssetsToSync.Emplace(Blueprint);
	}

	if (!AssetsToSync.IsEmpty())
	{
		GEditor->SyncBrowserToObjects(AssetsToSync);
	}

	return FReply::Handled();
}

FReply SGBAHeaderView::OpenAssetEditorClicked() const
{
	check(ViewModel.IsValid());
	
	if (UBlueprint* Blueprint = ViewModel->GetSelectedBlueprint().Get())
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Blueprint);
	}

	return FReply::Handled();
}

FText SGBAHeaderView::GetRequiredModuleDependenciesText() const
{
	check(ViewModel.IsValid());
	const int32 RequiredModuleDependenciesCount = ViewModel->GetRequiredModuleDependencies().Num();
	const int32 MissingModuleDependenciesCount = ViewModel->GetMissingModuleDependencies().Num();
	return FText::Format(
		LOCTEXT("RequiredModuleDependencies", "Required Module Dependencies ({0}/{1})"),
		FText::AsNumber(RequiredModuleDependenciesCount - MissingModuleDependenciesCount),
		FText::AsNumber(RequiredModuleDependenciesCount)
	);
}

FText SGBAHeaderView::GetRequiredModuleDependenciesTooltipText() const
{
	check(ViewModel.IsValid());
	const TArray<FGBARequiredModuleDependency> RequiredModuleDependencies = ViewModel->GetRequiredModuleDependencies();
	const TArray<FString> MissingModuleDependencies = ViewModel->GetMissingModuleDependencies();
	
	const FString ModuleDependenciesText = FString::JoinBy(RequiredModuleDependencies, TEXT("\n- "), [](const FGBARequiredModuleDependency& Item)
	{
		return Item.ToString();
	});

	const TSharedPtr<FModuleContextInfo> ModuleContextInfo = ViewModel->GetSelectedModuleInfo();

	const FString Filename = FGBAScaffoldUtils::GetModuleBuildCSFilename(*ModuleContextInfo);
	FString FilePath = FGBAScaffoldUtils::GetModuleBuildCSFilePath(*ModuleContextInfo);
	FilePath.RemoveFromStart(FPaths::ProjectDir());

	const FText ShortIDEName = FSourceCodeNavigation::GetSelectedSourceCodeIDE();
	FText TooltipText = FText::Format(
		LOCTEXT(
			"RequiredModuleDependenciesTooltip",
			"(Click to open {0} in {1} code editor)\n\n"
			"Missing {2} module dependencies out of {3}. Required Module Dependencies:\n\n- {4}\n\n"
			"Module Build.cs: {5}"
		),
		FText::FromString(Filename),
		ShortIDEName,
		FText::AsNumber(MissingModuleDependencies.Num()),
		FText::AsNumber(RequiredModuleDependencies.Num()),
		FText::FromString(ModuleDependenciesText),
		FText::FromString(FilePath)
	);
	return TooltipText;
}

FReply SGBAHeaderView::HandleRequiredModuleDependenciesClicked() const
{
	const FString FilePath = FGBAScaffoldUtils::GetModuleBuildCSFilePath(*ViewModel->GetSelectedModuleInfo());

	if (!FModuleManager::Get().IsModuleLoaded("SourceCodeAccess"))
	{
		GBA_SCAFFOLD_LOG(Error, TEXT("Unable to access SourceCodeAccess module (not loaded) to open up module Build.cs file for %s"), *FilePath)
		return FReply::Handled();
	}

	const FText ShortIDEName = FSourceCodeNavigation::GetSelectedSourceCodeIDE();
	const FText SuggestedSourceCodeIDE = FSourceCodeNavigation::GetSuggestedSourceCodeIDE(true);
	
	GBA_SCAFFOLD_LOG(Verbose, TEXT("SGBAHeaderView::HandleRequiredModuleDependenciesClicked - Opening up %s file in %s"), *FilePath, *ShortIDEName.ToString())
	if (!FSourceCodeNavigation::OpenSourceFile(FilePath))
	{
		GBA_SCAFFOLD_LOG(Error, TEXT("FSourceCodeNavigation::OpenSourceFile() failed to open %s with %s"), *FilePath, *ShortIDEName.ToString())
		if (!FSourceCodeNavigation::IsCompilerAvailable())
		{
			GBA_SCAFFOLD_LOG(
				Error,
				TEXT("It appears your environment doesn't have a compiler available. Please install %s and try again"),
				*SuggestedSourceCodeIDE.ToString()
			)
		}
		
		return FReply::Handled();
	}
	
	return FReply::Handled();
}

FSlateColor SGBAHeaderView::GetRequiredModuleDependenciesIconColor() const
{
	check(ViewModel.IsValid());
	return ViewModel->GetbSatisfiesModuleDependencies() ? FStyleColors::AccentGreen : FStyleColors::AccentYellow;
}

const FSlateBrush* SGBAHeaderView::GetRequiredModuleDependenciesIcon() const
{
	const FName IconName = ViewModel->GetbSatisfiesModuleDependencies() ? TEXT("Icons.Check") : TEXT("Icons.WarningWithColor");
	return FAppStyle::Get().GetBrush(IconName);
}

#undef LOCTEXT_NAMESPACE
