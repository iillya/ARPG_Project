// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "SGBANewDataTableWindowContent.h"

#include "AssetViewUtils.h"
#include "AttributeSet.h"
#include "ContentBrowserModule.h"
#include "DataTableEditorModule.h"
#include "GBAEditorLog.h"
#include "IContentBrowserDataModule.h"
#include "IContentBrowserSingleton.h"
#include "PackageTools.h"
#include "SGBADataTableListViewRow.h"
#include "SPathPicker.h"
#include "SPrimaryButton.h"
#include "SWarningOrErrorBox.h"
#include "SlateOptMacros.h"
#include "Abilities/GBAAttributeSetBlueprintBase.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/Blueprint.h"
#include "Fonts/FontMeasure.h"
#include "Framework/Application/SlateApplication.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/EngineVersionComparison.h"
#include "Styling/GBAAppStyle.h"
#include "Subsystems/GBAEditorSubsystem.h"
#include "Utils/GBAUtils.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

const FName SGBANewDataTableWindowContent::RowNumberColumnId("RowNumber");
const FName SGBANewDataTableWindowContent::RowNameColumnId("RowName");

#define LOCTEXT_NAMESPACE "GBADataTableWindowContent"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

// ReSharper disable once CppParameterNeverUsed
void SGBANewDataTableWindowContent::Construct(const FArguments& InArgs, const TWeakObjectPtr<UBlueprint>& InBlueprint)
{
	const FMargin PaddingAmount = FMargin(18.f);

	check(InBlueprint.IsValid());
	Blueprint = InBlueprint;
	Blueprint->OnChanged().AddThreadSafeSP(this, &SGBANewDataTableWindowContent::HandleBlueprintChanged);

	// The containing folder in content browser for the edited blueprint
	const FString DefaultPackagePath = FPackageName::GetLongPackagePath(Blueprint->GetPathName());

	const FName VirtualPath = IContentBrowserDataModule::Get().GetSubsystem()->ConvertInternalPathToVirtual(*DefaultPackagePath);

	// Init view model
	ViewModel = MakeShared<FNewDataTableWindowViewModel>();
	ViewModel->SetSelectedPath(VirtualPath.ToString());
	ViewModel->SetAssetName(FString::Printf(TEXT("DT_%s"), *FGBAUtils::GetAttributeClassName(InBlueprint->GeneratedClass)));
	ViewModel->OnModelPropertyChanged().AddThreadSafeSP(this, &SGBANewDataTableWindowContent::HandleModelPropertyChanged);

	FPathPickerConfig PathPickerConfig;
	PathPickerConfig.DefaultPath = DefaultPackagePath;
	PathPickerConfig.bFocusSearchBoxWhenOpened = false;
	PathPickerConfig.OnPathSelected = FOnPathSelected::CreateSP(this, &SGBANewDataTableWindowContent::HandlePathSelected);
	PathPickerConfig.bOnPathSelectedPassesVirtualPaths = true;

	const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	PathPicker = StaticCastSharedRef<SPathPicker>(ContentBrowserModule.Get().CreatePathPicker(PathPickerConfig));

	const TSharedRef<SScrollBar> VerticalScrollBar = SNew(SScrollBar)
		.Orientation(Orient_Vertical)
		.Thickness(FVector2D(12.0f, 12.0f));

	const TSharedRef<SScrollBar> HorizontalScrollBar = SNew(SScrollBar)
		.Orientation(Orient_Horizontal)
		.Thickness(FVector2D(12.0f, 12.0f));

	ColumnNamesHeaderRow = SNew(SHeaderRow);

	CellsListView = SNew(SListView<FDataTableEditorRowListViewDataPtr>)
		.ListItemsSource(&AvailableRows)
		.HeaderRow(ColumnNamesHeaderRow)
		.OnGenerateRow(this, &SGBANewDataTableWindowContent::MakeRowWidget)
		.ExternalScrollbar(VerticalScrollBar)
		.ConsumeMouseWheel(EConsumeMouseWheel::Always)
		.SelectionMode(ESelectionMode::Single)
		.AllowOverscroll(EAllowOverscroll::No);

	const FString CSV = GenerateCSVFromBlueprintAttributes(Blueprint);
	GBA_EDITOR_LOG(Verbose, TEXT("CSV Result:\n\n%s"), *CSV)

	UDataTable* DataTable = NewObject<UDataTable>(GetTransientPackage(), UDataTable::StaticClass());
	DataTable->RowStruct = FAttributeMetaData::StaticStruct();
	DataTable->CreateTableFromCSVString(CSV);
	BuildDataColumnsAndRows(DataTable);

	ChildSlot
	[
		SNew(SBorder)
		.Padding(PaddingAmount)
		.BorderImage(FGBAAppStyle::GetBrush(TEXT("Docking.Tab.ContentAreaBrush")))
		[
			SNew(SVerticalBox)
			// +SVerticalBox::Slot()
			// .AutoHeight()
			// .Padding(0, 0, 0, 4)
			// [
			// 	SNew(SBorder)
			// 	.Padding(PaddingAmount)
			// 	.BorderImage(FGBAAppStyle::GetBrush(TEXT("DetailsView.CategoryTop")))
			// 	[
			// 		SNew(STextBlock)
			// 		.Text(LOCTEXT("Description", "Click the button below ..."))
			// 		.Font(FStyleFonts::Get().NormalBold)
			// 	]
			// ]

			+SVerticalBox::Slot()
			.FillHeight(1.f)
			.Padding(0, 0, 0, 4)
			[
				SNew(SSplitter)
				+SSplitter::Slot()
				.Value(0.25f)
				[
					SNew(SBorder)
					.BorderImage(FGBAAppStyle::GetBrush("ToolPanel.GroupBorder"))
					[
						PathPicker.ToSharedRef()
					]
				]

				+SSplitter::Slot()
				.Value(0.75f)
				[
					SNew(SBorder)
					.BorderImage(FGBAAppStyle::GetBrush("ToolPanel.GroupBorder"))
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.FillHeight(1.f)
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							.FillWidth(1.f)
							[
								CellsListView.ToSharedRef()

							]
							+SHorizontalBox::Slot()
							.AutoWidth()
							[
								VerticalScrollBar
							]
						]

						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							[
								HorizontalScrollBar
							]
						]
					]
				]
			]

			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(WarningOrErrorSwitcher, SWidgetSwitcher)
				+SWidgetSwitcher::Slot()
				[
					SAssignNew(ErrorBox, SWarningOrErrorBox)
					.Padding(FMargin(8.f))
					.IconSize(FVector2D(16, 16))
					.MessageStyle(EMessageStyle::Error)
					.Message(this, &SGBANewDataTableWindowContent::GetNameErrorLabelText)
					.Visibility(this, &SGBANewDataTableWindowContent::GetNameErrorLabelVisibility)
				]
				+SWidgetSwitcher::Slot()
				[
					SAssignNew(WarningBox, SWarningOrErrorBox)
					.Padding(FMargin(8.f))
					.IconSize(FVector2D(16, 16))
					.MessageStyle(EMessageStyle::Warning)
					.Message(this, &SGBANewDataTableWindowContent::GetNameWarningLabelText)
					.Visibility(this, &SGBANewDataTableWindowContent::GetNameWarningLabelVisibility)
				]
			]

			+SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.Padding(16.f, 4.f, 16.f, 16.f)
			[

				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Bottom)
				.Padding(0.f, 0.f, 4.f, 0.f)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.FillHeight(1.f)
					.VAlign(VAlign_Center)
					.Padding(0, 4, 0, 4)
					[
						SNew(STextBlock).Text(LOCTEXT("PathBoxLabel", "Path:"))
					]

					+SVerticalBox::Slot()
					.FillHeight(1)
					.VAlign(VAlign_Center)
					.Padding(0, 4, 0, 4)
					[
						SNew(STextBlock).Text(LOCTEXT("NameBoxLabel", "Name:"))
					]
				]
				+SHorizontalBox::Slot()
				.FillWidth(1)
				.VAlign(VAlign_Bottom)
				.Padding(4.f, 0.f)
				[

					SNew(SVerticalBox)

					+SVerticalBox::Slot()
					.FillHeight(1)
					.VAlign(VAlign_Center)
					.Padding(0, 4, 0, 4)
					[

						SAssignNew(PathText, STextBlock)
						.Text(this, &SGBANewDataTableWindowContent::GetPathNameText)
					]

					+SVerticalBox::Slot()
					.AutoHeight()
					.VAlign(VAlign_Center)
					.Padding(0, 0, 0, 0)
					[
						SAssignNew(NameEditableText, SEditableTextBox)
						.Text(this, &SGBANewDataTableWindowContent::GetAssetNameText)
						.OnTextCommitted(this, &SGBANewDataTableWindowContent::HandleAssetNameTextCommitted)
						.OnTextChanged(this, &SGBANewDataTableWindowContent::HandleAssetNameTextCommitted, ETextCommit::Default)
						.SelectAllTextWhenFocused(true)
					]
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Bottom)
				.Padding(4.f, 0.f)
				[
					SNew(SPrimaryButton)
					.Text(LOCTEXT("ButtonLabel", "Save"))
					.IsEnabled(this, &SGBANewDataTableWindowContent::IsConfirmButtonEnabled)
					.OnClicked(this, &SGBANewDataTableWindowContent::OnConfirmClicked)
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Bottom)
				.Padding(4.f, 0.f, 0.0f, 0.0f)
				[
					SNew(SButton)
					.TextStyle(FAppStyle::Get(), "DialogButtonText")
					.Text(LOCTEXT("AssetDialogCancelButton", "Cancel"))
					.OnClicked(this, &SGBANewDataTableWindowContent::OnCancelClicked)
				]
			]
		]
	];

	UpdateInputValidity();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

SGBANewDataTableWindowContent::~SGBANewDataTableWindowContent()
{
	if (Blueprint.IsValid())
	{
		Blueprint->OnChanged().RemoveAll(this);
	}
}

FString SGBANewDataTableWindowContent::GenerateCSVFromBlueprintAttributes(const TWeakObjectPtr<UBlueprint>& InBlueprint)
{
	check(InBlueprint.IsValid());
	check(InBlueprint->SkeletonGeneratedClass);

	FString CSV;

	const UClass* OwnerClass = InBlueprint->GeneratedClass;

	TArray<FProperty*> Properties;
	FGBAUtils::GetAllAttributeFromClass(OwnerClass, Properties);

	GBA_EDITOR_LOG(
		Verbose,
		TEXT("SGBANewDataTableWindowContent::GenerateCSVFromBlueprintAttributes Blueprint: %s, Properties: %d"),
		*GetNameSafe(InBlueprint.Get()),
		Properties.Num()
	)

	UAttributeSet* CDO = Cast<UAttributeSet>(OwnerClass->GetDefaultObject());
	if (!ensureMsgf(CDO, TEXT("Invalid CDO couldn't cast to UAttributeSet from %s"), *GetNameSafe(OwnerClass)))
	{
		return CSV;
	}

	CSV.Append(TEXT("---,BaseValue,MinValue,MaxValue,DerivedAttributeInfo,bCanStack"));
	const FString AttributeClassName = FGBAUtils::GetAttributeClassName(OwnerClass);

	for (const FProperty* Property : Properties)
	{
		GBA_EDITOR_LOG(Verbose, TEXT("\tProperty: %s (OwnerClass: %s, CDO: %s)"), *GetNameSafe(Property), *GetNameSafe(OwnerClass), *GetNameSafe(CDO))
		if (!FGameplayAttribute::IsGameplayAttributeDataProperty(Property))
		{
			continue;
		}

		FGameplayAttribute Attribute = FindFProperty<FProperty>(OwnerClass, Property->GetFName());
		if (UGBAAttributeSetBlueprintBase::IsGameplayAttributeDataClampedProperty(Property))
		{
			if (const FGBAGameplayClampedAttributeData* Clamped = static_cast<FGBAGameplayClampedAttributeData*>(Attribute.GetGameplayAttributeData(CDO)))
			{
				const float MinValue = Clamped->MinValue.GetValueForClamping(CDO);
				const float MaxValue = Clamped->MaxValue.GetValueForClamping(CDO);
				
				CSV.Append(FString::Printf(
					TEXT("\r\n%s.%s,\"%f\",\"%f\",\"%f\",\"\",\"False\""),
					*AttributeClassName,
					*GetNameSafe(Property),
					Clamped->GetBaseValue(),
					MinValue,
					MaxValue
				));
			}
		}
		else
		{
			const FGameplayAttributeData* AttributeData = Attribute.GetGameplayAttributeDataChecked(CDO);
			check(AttributeData);

			CSV.Append(FString::Printf(
				TEXT("\r\n%s.%s,\"%f\",\"%f\",\"%f\",\"\",\"False\""),
				*AttributeClassName,
				*GetNameSafe(Property),
				AttributeData->GetBaseValue(),
				0.f,
				0.f
			));
		}
	}

	return CSV;
}

void SGBANewDataTableWindowContent::HandleBlueprintChanged(UBlueprint* InBlueprint)
{
	GBA_EDITOR_LOG(Verbose, TEXT("SGBANewDataTableWindowContent::HandleBlueprintChanged %s"), *GetNameSafe(InBlueprint))

	const FString CSV = GenerateCSVFromBlueprintAttributes(InBlueprint);
	GBA_EDITOR_LOG(Verbose, TEXT("CSV Result:\n\n%s"), *CSV)

	UDataTable* DataTable = NewObject<UDataTable>(GetTransientPackage(), UDataTable::StaticClass());
	DataTable->RowStruct = FAttributeMetaData::StaticStruct();
	DataTable->CreateTableFromCSVString(CSV);

	AvailableColumns.Reset();
	AvailableRows.Reset();
	ColumnNamesHeaderRow->ClearColumns();
	RowNameColumnWidth = 0;
	RowNumberColumnWidth = 0;

	BuildDataColumnsAndRows(DataTable);
	CellsListView->RequestListRefresh();
}

void SGBANewDataTableWindowContent::HandleModelPropertyChanged(const FString& InPropertyChanged)
{
	check(ViewModel.IsValid())
	GBA_EDITOR_LOG(Verbose, TEXT("SGBANewDataTableWindowContent::HandleModelPropertyChanged - Property %s, Model: %s"), *InPropertyChanged, *ViewModel->ToString());
	UpdateInputValidity();
}

void SGBANewDataTableWindowContent::UpdateInputValidity()
{
	bLastInputValidityCheckSuccessful = true;
	bLastInputValidityWarningSuccessful = true;
	check(ViewModel.IsValid())

	const FString CurrentlyEnteredAssetName = ViewModel->GetAssetName();
	const FString CurrentlySelectedPath = ViewModel->GetSelectedPath();

	// No error text for an empty name. Just fail validity.
	if (CurrentlyEnteredAssetName.IsEmpty())
	{
		SetError(FText::GetEmpty());
		return;
	}

	FName ConvertedPath;
	const EContentBrowserPathType ConvertedType = IContentBrowserDataModule::Get().GetSubsystem()->TryConvertVirtualPath(CurrentlySelectedPath, ConvertedPath);
	GBA_EDITOR_LOG(
		Verbose,
		TEXT("SGBANewDataTableWindowContent::UpdateInputValidity CurrentlySelectedPath: %s, ConvertedPath: %s, ConvertedType: %s"),
		*CurrentlySelectedPath,
		*ConvertedPath.ToString(),
		*UEnum::GetValueAsString(ConvertedType)
	)

	// Check for path validity
	bool bIsMountedInternalPath = false;
	if (ConvertedType == EContentBrowserPathType::Internal)
	{
		FString CheckPath = ConvertedPath.ToString();
		if (!CheckPath.EndsWith(TEXT("/")))
		{
			CheckPath += TEXT("/");
		}

		if (FPackageName::IsValidPath(CheckPath))
		{
			bIsMountedInternalPath = true;
		}
	}

	// Not a valid mounted path
	if (!bIsMountedInternalPath)
	{
		SetError(LOCTEXT("VirtualPathSelected", "The selected folder cannot be modified."));
		return;
	}

	// Check for object path and correct asset name (eg. no invalid characters, etc.), also against existing files raising an error
	// if the existing file is not a UDataTable
	FText ErrorMessage;
	const FString ObjectPath = GetObjectPathForSave();
	if (!AssetViewUtils::IsValidObjectPathForCreate(ObjectPath, UDataTable::StaticClass(), ErrorMessage, true))
	{
		SetError(ErrorMessage);
		return;
	}

	// Check for an existing asset
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
#if UE_VERSION_NEWER_THAN(5, 1, -1)
	FAssetData ExistingAsset = AssetRegistryModule.Get().GetAssetByObjectPath(FSoftObjectPath(ObjectPath));
#else
	FAssetData ExistingAsset = AssetRegistryModule.Get().GetAssetByObjectPath(FName(*ObjectPath));
#endif
	if (ExistingAsset.IsValid())
	{
		FString ObjectName = FPackageName::ObjectPathToObjectName(ObjectPath);

		// An asset of a different type already exists at this location, inform the user and continue
		if (!ExistingAsset.IsInstanceOf(UDataTable::StaticClass()))
		{
			SetError(FText::Format(
				LOCTEXT("OtherTypeAlreadyExists", "An asset of type '{0}' already exists at this location with the name '{1}'."),
				
#if UE_VERSION_NEWER_THAN(5, 1, -1)
				FText::FromString(ExistingAsset.AssetClassPath.ToString()),
#else
				FText::FromName(ExistingAsset.AssetClass),
#endif
				FText::FromString(ObjectName)
			));

			return;
		}

		// An asset of expected DataTable type already exists, check for MetaData RowStructure
		FString RowStructure = ExistingAsset.GetTagValueRef<FString>(TEXT("RowStructure"));
		// Normalize between short name (5.0) and long path name (5.1)
		if (RowStructure.Contains(TEXT("/")))
		{
			// We dealing with long path, get the Struct short name
			FString LeftS;
			FString RightS;
			RowStructure.Split(TEXT("."), &LeftS, &RightS);
			if (!RightS.IsEmpty())
			{
				RowStructure = RightS;
			}
		}
		
		if (RowStructure != TEXT("AttributeMetaData"))
		{
			SetError(FText::Format(
				LOCTEXT("DataTableOtherTypeAlreadyExists", "A DataTable asset with RowStructure of type '{0}' (must be GameplayAbilities.AttributeMetaData) already exists at this location with the name '{1}'."),
				FText::FromString(RowStructure),
				FText::FromString(ObjectName)
			));

			return;
		}

		// This asset already exists at this location, warn user if asked to.
		const FText NewErrorMessage = FText::Format(
			LOCTEXT(
				"Error_ExistingDataTable",
				"An asset already exists at this location with the name '{0}'. "
				"(If you proceed, the existing DataTable will be updated with the content above)"
			),
			FText::FromString(ObjectName)
		);
		SetWarning(NewErrorMessage);
	}
}

void SGBANewDataTableWindowContent::SetError(const FText& InErrorText)
{
	LastInputValidityErrorText = InErrorText;
	bLastInputValidityCheckSuccessful = false;
	bLastInputValidityWarningSuccessful = true;
	if (WarningOrErrorSwitcher.IsValid())
	{
		WarningOrErrorSwitcher->SetActiveWidget(ErrorBox.ToSharedRef());
	}
}

void SGBANewDataTableWindowContent::SetWarning(const FText& InWarningText)
{
	LastInputValidityErrorText = InWarningText;
	bLastInputValidityCheckSuccessful = true;
	bLastInputValidityWarningSuccessful = false;
	if (WarningOrErrorSwitcher.IsValid())
	{
		WarningOrErrorSwitcher->SetActiveWidget(WarningBox.ToSharedRef());
	}
}

void SGBANewDataTableWindowContent::BuildDataColumnsAndRows(const UDataTable* InDataTable)
{
	FDataTableEditorUtils::CacheDataTableForEditing(InDataTable, AvailableColumns, AvailableRows);

	// Update the desired width of the row names and numbers column
	// This prevents it growing or shrinking as you scroll the list view
	RefreshRowNameColumnWidth();
	RefreshRowNumberColumnWidth();

	ColumnNamesHeaderRow->AddColumn(
		SHeaderRow::Column(RowNumberColumnId)
		.FixedWidth(RowNumberColumnWidth)
		[
			SNew(STextBlock)
			.Text(FText::GetEmpty())
		]
	);

	ColumnNamesHeaderRow->AddColumn(
		SHeaderRow::Column(RowNameColumnId)
		.DefaultLabel(LOCTEXT("DataTableRowName", "Row Name"))
		.ManualWidth(RowNameColumnWidth)
	);

	float TotalWidth = 0.f;
	for (const TSharedPtr<FDataTableEditorColumnHeaderData>& Column : AvailableColumns)
	{
		TotalWidth += Column->DesiredColumnWidth;
	}
	check(TotalWidth != 0);

	GBA_EDITOR_LOG(Verbose, TEXT("SGBANewDataTableWindowContent::BuildDataColumnsAndRows AvailableColumns: %d (TotalWidth: %f)"), AvailableColumns.Num(), TotalWidth);
	for (const TSharedPtr<FDataTableEditorColumnHeaderData>& Column : AvailableColumns)
	{
		const float DesiredFillWidth = Column->DesiredColumnWidth / TotalWidth;
		GBA_EDITOR_LOG(
			Verbose,
			TEXT("\t ColumnId: %s, DisplayName: %s, DesiredColumnWidth: %f, DesiredFillWidth: %f"),
			*Column->ColumnId.ToString(),
			*Column->DisplayName.ToString(),
			Column->DesiredColumnWidth,
			DesiredFillWidth
		);

		ColumnNamesHeaderRow->AddColumn(
			SHeaderRow::Column(Column->ColumnId)
			.DefaultLabel(Column->DisplayName)
			.FillWidth(DesiredFillWidth)
		);
	}
}


TSharedRef<ITableRow> SGBANewDataTableWindowContent::MakeRowWidget(const FDataTableEditorRowListViewDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SGBADataTableListViewRow, OwnerTable)
		.HostWidget(SharedThis(this))
		.RowDataPtr(InRowDataPtr);
}

void SGBANewDataTableWindowContent::HandlePathSelected(const FString& InPath) const
{
	check(ViewModel.IsValid());
	ViewModel->SetSelectedPath(InPath);
}

EVisibility SGBANewDataTableWindowContent::GetNameErrorLabelVisibility() const
{
	return GetNameErrorLabelText().IsEmpty() ? EVisibility::Hidden : EVisibility::Visible;
}

FText SGBANewDataTableWindowContent::GetNameErrorLabelText() const
{
	if (!bLastInputValidityCheckSuccessful)
	{
		return LastInputValidityErrorText;
	}

	return FText::GetEmpty();
}

EVisibility SGBANewDataTableWindowContent::GetNameWarningLabelVisibility() const
{
	return GetNameWarningLabelText().IsEmpty() ? EVisibility::Hidden : EVisibility::Visible;
}

FText SGBANewDataTableWindowContent::GetNameWarningLabelText() const
{
	if (!bLastInputValidityWarningSuccessful)
	{
		return LastInputValidityErrorText;
	}

	return FText::GetEmpty();
}

FText SGBANewDataTableWindowContent::GetPathNameText() const
{
	check(ViewModel.IsValid())
	return FText::FromString(ViewModel->GetSelectedPath());
}

FText SGBANewDataTableWindowContent::GetAssetNameText() const
{
	check(ViewModel.IsValid())
	return FText::FromString(ViewModel->GetAssetName());
}

// ReSharper disable once CppParameterNeverUsed
void SGBANewDataTableWindowContent::HandleAssetNameTextCommitted(const FText& InText, ETextCommit::Type InCommitType) const
{
	check(ViewModel.IsValid())
	ViewModel->SetAssetName(InText.ToString());
}

bool SGBANewDataTableWindowContent::IsConfirmButtonEnabled() const
{
	return bLastInputValidityCheckSuccessful;
}

FReply SGBANewDataTableWindowContent::OnConfirmClicked()
{
	check(Blueprint.IsValid());

	const FString PackageName = UPackageTools::SanitizePackageName(GetObjectPathForSave(false));
	UPackage* Pkg = CreatePackage(*PackageName);
	if (!ensure(Pkg))
	{
		CloseDialog();
		// Failed to create the package to hold this asset for some reason
		return FReply::Handled();
	}

	// Make sure the destination package is loaded
	Pkg->FullyLoad();

	constexpr EObjectFlags Flags = RF_Public | RF_Standalone | RF_Transactional;
	UDataTable* NewDataTable = NewObject<UDataTable>(Pkg, UDataTable::StaticClass(), FName(*ViewModel->GetAssetName()), Flags);
	NewDataTable->RowStruct = FAttributeMetaData::StaticStruct();
	NewDataTable->CreateTableFromCSVString(GenerateCSVFromBlueprintAttributes(Blueprint));

	// Close editor if existing asset already and is currently opened
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
#if UE_VERSION_NEWER_THAN(5, 1, -1)
	const FAssetData ExistingAsset = AssetRegistryModule.Get().GetAssetByObjectPath(FSoftObjectPath(GetObjectPathForSave()));
#else
	const FAssetData ExistingAsset = AssetRegistryModule.Get().GetAssetByObjectPath(FName(*GetObjectPathForSave()));
#endif

	if (ExistingAsset.IsValid())
	{
		TArray<FAssetData> ClosedAssets;
		UGBAEditorSubsystem::Get().CloseEditors({ExistingAsset}, ClosedAssets);
	}

	FDataTableEditorModule& DataTableEditorModule = FModuleManager::LoadModuleChecked<FDataTableEditorModule>("DataTableEditor");
	DataTableEditorModule.CreateDataTableEditor(EToolkitMode::Standalone, nullptr, NewDataTable);

	CloseDialog();

	return FReply::Handled();
}

FReply SGBANewDataTableWindowContent::OnCancelClicked()
{
	CloseDialog();

	return FReply::Handled();
}

void SGBANewDataTableWindowContent::CloseDialog()
{
	const TSharedPtr<SWindow> ContainingWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());

	if (ContainingWindow.IsValid())
	{
		ContainingWindow->RequestDestroyWindow();
	}
}

void SGBANewDataTableWindowContent::RefreshRowNameColumnWidth()
{
	RowNameColumnWidth = CalculateColumnWidth(RowNameColumnWidth, ECalculateColumnType::DisplayName);
	// Add slight offset padding to display full text for longest column width
	RowNameColumnWidth += 20.f;
}

void SGBANewDataTableWindowContent::RefreshRowNumberColumnWidth()
{
	RowNumberColumnWidth = CalculateColumnWidth(RowNumberColumnWidth, ECalculateColumnType::RowNum);
}

float SGBANewDataTableWindowContent::CalculateColumnWidth(const float InInitialValue, const ECalculateColumnType InColumnType)
{
	const TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	const FTextBlockStyle& CellTextStyle = FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>("DataTableEditor.CellText");
	constexpr float CellPadding = 10.0f;

	float Result = InInitialValue;

	for (const FDataTableEditorRowListViewDataPtr& RowData : AvailableRows)
	{
		FVector2D Measure;
		if (InColumnType == ECalculateColumnType::RowNum)
		{
			Measure = FontMeasure->Measure(FString::FromInt(RowData->RowNum), CellTextStyle.Font);
		}
		else if (InColumnType == ECalculateColumnType::DisplayName)
		{
			Measure = FontMeasure->Measure(RowData->DisplayName, CellTextStyle.Font);
		}
		else
		{
			checkf(false, TEXT("Unsupported column type"))
		}

		const float MeasureWidth = static_cast<float>(Measure.X) + CellPadding;
		Result = FMath::Max(Result, MeasureWidth);
	}

	return Result;
}

FString SGBANewDataTableWindowContent::GetObjectPathForSave(const bool bInIsLongPath) const
{
	check(ViewModel.IsValid())
	const FString CurrentlySelectedPath = ViewModel->GetSelectedPath();
	const FString CurrentlyEnteredAssetName = ViewModel->GetAssetName();

	FName ConvertedPath;
	const EContentBrowserPathType ConvertedType = IContentBrowserDataModule::Get().GetSubsystem()->TryConvertVirtualPath(CurrentlySelectedPath, ConvertedPath);
	if (ConvertedType != EContentBrowserPathType::Internal)
	{
		return FString();
	}

	if (!bInIsLongPath)
	{
		return ConvertedPath.ToString() / CurrentlyEnteredAssetName;
	}

	return ConvertedPath.ToString() / CurrentlyEnteredAssetName + TEXT(".") + CurrentlyEnteredAssetName;
}

#undef LOCTEXT_NAMESPACE
