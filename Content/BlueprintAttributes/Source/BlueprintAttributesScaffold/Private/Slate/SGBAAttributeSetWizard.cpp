// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "SGBAAttributeSetWizard.h"

#include "AttributeSet.h"
#include "GBAScaffoldLog.h"
#include "GBAScaffoldUtils.h"
#include "SGBAClassInfo.h"
#include "SGBAHeaderView.h"
#include "SGBASuggestedIDEWidget.h"
#include "SlateOptMacros.h"
#include "SourceCodeNavigation.h"
#include "AssetRegistry/AssetData.h"
#include "Engine/Blueprint.h"
#include "Misc/MessageDialog.h"
#include "Models/GBAAttributeSetWizardViewModel.h"
#include "Styling/GBAAppStyle.h"
#include "Widgets/Workflow/SWizard.h"

#define LOCTEXT_NAMESPACE "SGBAHeaderView"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

// ReSharper disable once CppParameterNeverUsed
void SGBAAttributeSetWizard::Construct(const FArguments& InArgs, const FAssetData& InAssetData)
{
	const FMargin PaddingAmount = FMargin(18.f);
	const FMargin PaddingInternalAmount = FMargin(0.f, 0.f, 0.f, 0.f);

	ViewModel = MakeShared<FGBAAttributeSetWizardViewModel>(UAttributeSet::StaticClass());
	ViewModel->Initialize();
	
	AssetData = InAssetData;
	ViewModel->SetNewClassName(GetBlueprintName(InAssetData));

	ViewModel->OnParentClassInfoChanged().AddSP(this, &SGBAAttributeSetWizard::HandleClassInfoChanged);
	ViewModel->OnSelectedModuleInfoChanged().AddSP(this, &SGBAAttributeSetWizard::HandleSelectedModuleInfoChanged);
	ViewModel->OnSelectedBlueprintChanged().AddSP(this, &SGBAAttributeSetWizard::HandleSelectedBlueprintChanged);

	ChildSlot
	[
		SNew(SBorder)
		.Padding(PaddingAmount)
		.BorderImage(FGBAAppStyle::GetBrush(TEXT("Docking.Tab.ContentAreaBrush")))
		[
			SAssignNew(Wizard, SWizard)
			.ShowPageList(false)
			.CanFinish(this, &SGBAAttributeSetWizard::CanFinish)
			.FinishButtonText(LOCTEXT("FinishButtonText_Native", "Create Class"))
			.FinishButtonToolTip(LOCTEXT("FinishButtonToolTip_Native", "Creates the code files to add your new class."))
			.OnCanceled(this, &SGBAAttributeSetWizard::CancelClicked)
			.OnFinished(this, &SGBAAttributeSetWizard::FinishClicked)
			.PageFooter()
			[
				// Get IDE information
				SNew(SBorder)
				.Visibility(this, &SGBAAttributeSetWizard::GetGlobalErrorLabelVisibility)
				.BorderImage(FAppStyle::Get().GetBrush("RoundedError"))
				.Padding(FMargin(8.f))
				.Content()
				[
					SNew(SHorizontalBox)

					+SHorizontalBox::Slot()
					.VAlign(VAlign_Top)
					.Padding(0.f, 0.f, 8.f, 0.f)
					.AutoWidth()
					[
						SNew(SImage)
						.Image(FAppStyle::Get().GetBrush("Icons.ErrorWithColor"))
					]

					+SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(this, &SGBAAttributeSetWizard::GetGlobalErrorLabelText)
						.AutoWrapText(true)
					]

					+SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					.AutoWidth()
					.Padding(5.f, 0.f)
					[
						SNew(SGBASuggestedIDEWidget)
					]
				]
			]

			// Name class
			+SWizard::Page()
			[
				SNew(SVerticalBox)

				+SVerticalBox::Slot()
				.AutoHeight()
				.Padding(PaddingInternalAmount)
				[
					SNew(SGBAClassInfo, ViewModel)
				]

				+SVerticalBox::Slot()
				.Padding(PaddingInternalAmount)
				[
					SAssignNew(HeaderViewWidget, SGBAHeaderView, InAssetData, ViewModel)
				]
			]
		]
	];

	ViewModel->UpdateInputValidity();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

SGBAAttributeSetWizard::~SGBAAttributeSetWizard()
{
}

void SGBAAttributeSetWizard::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	check(ViewModel.IsValid());
	ViewModel->RunPeriodicValidationOnTick(InCurrentTime);
}

void SGBAAttributeSetWizard::CancelClicked()
{
	CloseContainingWindow();
}

bool SGBAAttributeSetWizard::CanFinish() const
{
	check(ViewModel.IsValid());
	return ViewModel->IsLastInputValidityCheckSuccessful() && FSourceCodeNavigation::IsCompilerAvailable();
}

void SGBAAttributeSetWizard::FinishClicked()
{
	check(CanFinish());
	check(ViewModel.IsValid());

	GBA_SCAFFOLD_LOG(Verbose, TEXT("Finish clicked, generate class now"))

	const FString NewClassName = ViewModel->GetNewClassName();
	const FString SelectedClassPath = ViewModel->GetSelectedClassPath();
	const FString NewClassPath = ViewModel->GetNewClassPath();
	const FString CalculatedClassHeaderName = ViewModel->GetCalculatedClassHeaderName();
	const FString CalculatedClassSourceName = ViewModel->GetCalculatedClassSourceName();
	const TSharedPtr<FModuleContextInfo> SelectedModuleInfo = ViewModel->GetSelectedModuleInfo();

	GBA_SCAFFOLD_LOG(Verbose, TEXT("\t NewClassName: %s"), *NewClassName)
	GBA_SCAFFOLD_LOG(Verbose, TEXT("\t SelectedClassPath: %s"), *SelectedClassPath)
	GBA_SCAFFOLD_LOG(Verbose, TEXT("\t NewClassPath: %s"), *NewClassPath)
	GBA_SCAFFOLD_LOG(Verbose, TEXT("\t CalculatedClassHeaderName: %s"), *CalculatedClassHeaderName)
	GBA_SCAFFOLD_LOG(Verbose, TEXT("\t CalculatedClassSourceName: %s"), *CalculatedClassSourceName)

	if (SelectedModuleInfo.IsValid())
	{
		GBA_SCAFFOLD_LOG(Verbose, TEXT("\t SelectedModuleInfo - ModuleSourcePath: %s"), *SelectedModuleInfo->ModuleSourcePath)
		GBA_SCAFFOLD_LOG(Verbose, TEXT("\t SelectedModuleInfo - ModuleName: %s"), *SelectedModuleInfo->ModuleName)
	}
	else
	{
		GBA_SCAFFOLD_LOG(Error, TEXT("Invalid module info"))
		CloseContainingWindow();
		return;
	}


	const FString HeaderContent = HeaderViewWidget->GetHeaderContent();
	const FString SourceContent = HeaderViewWidget->GetSourceContent();

	const FString HeaderDestination = CalculatedClassHeaderName;
	const FString SourceDestination = CalculatedClassSourceName;

	// Generate Class
	FText ErrorText;
	GameProjectUtils::EReloadStatus HotReloadStatus;
	const GameProjectUtils::EAddCodeToProjectResult Result = FGBAScaffoldUtils::AddClassToProject(
		NewClassName,
		NewClassPath,
		HeaderDestination,
		HeaderContent,
		SourceDestination,
		SourceContent,
		*SelectedModuleInfo.Get(),
		HotReloadStatus,
		ErrorText
	);
	
	if (Result != GameProjectUtils::EAddCodeToProjectResult::Succeeded)
	{
		CloseContainingWindow();
		
		GBA_SCAFFOLD_LOG(Error, TEXT("Failed to generate class: %s"), *ErrorText.ToString())
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("GenFailed", "Failed to generate class - Reason: {0}"), ErrorText));
		return;
	}

	CloseContainingWindow();
}

void SGBAAttributeSetWizard::CloseContainingWindow()
{
	const TSharedPtr<SWindow> ContainingWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
	if (ContainingWindow.IsValid())
	{
		ContainingWindow->RequestDestroyWindow();
	}
}

FString SGBAAttributeSetWizard::GetBlueprintName(const FAssetData& InAssetData)
{
	if (const UBlueprint* Blueprint = Cast<UBlueprint>(InAssetData.GetAsset()))
	{
		return Blueprint->GetName();
	}

	return TEXT("");
}

EVisibility SGBAAttributeSetWizard::GetGlobalErrorLabelVisibility() const
{
	return GetGlobalErrorLabelText().IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible;
}

FText SGBAAttributeSetWizard::GetGlobalErrorLabelText() const
{
	// Check environment first, and warn if compiler is not available
	if (!FSourceCodeNavigation::IsCompilerAvailable())
	{
#if PLATFORM_LINUX
		return FText::Format(LOCTEXT("NoCompilerFoundNewClassLinux", "In order to create a C++ class, you must first install {0}."), FSourceCodeNavigation::GetSuggestedSourceCodeIDE());
#else
		return FText::Format(LOCTEXT("NoCompilerFoundNewClass", "No compiler was found. In order to create C++ code, you must first install {0}."), FSourceCodeNavigation::GetSuggestedSourceCodeIDE());
#endif
	}

	check(ViewModel.IsValid());

	// Then display any errors returned by ClassInfo widget
	if (!ViewModel->IsLastInputValidityCheckSuccessful())
	{
		return ViewModel->GetLastInputValidityErrorText();
	}

	return FText::GetEmpty();
}

void SGBAAttributeSetWizard::HandleClassInfoChanged(const FNewClassInfo& InOldClassInfo, const FNewClassInfo& InNewClassInfo) const
{
	UpdateRequiredModuleDependenciesIfNeeded();
}

void SGBAAttributeSetWizard::HandleSelectedModuleInfoChanged(const TSharedPtr<FModuleContextInfo>& InOldModuleContextInfo, const TSharedPtr<FModuleContextInfo>& InNewModuleContextInfo) const
{
	UpdateRequiredModuleDependenciesIfNeeded();
}

void SGBAAttributeSetWizard::HandleSelectedBlueprintChanged(const TWeakObjectPtr<UBlueprint>& InOldBlueprint, const TWeakObjectPtr<UBlueprint>& InNewBlueprint) const
{
	UpdateRequiredModuleDependenciesIfNeeded();
}

void SGBAAttributeSetWizard::UpdateRequiredModuleDependenciesIfNeeded() const
{
	check(ViewModel.IsValid());

	ViewModel->ResetRequiredModuleDependencies();

	const FNewClassInfo ParentClassInfo = ViewModel->GetParentClassInfo();
	TSharedPtr<FModuleContextInfo> ModuleContextInfo = ViewModel->GetSelectedModuleInfo();
	const TWeakObjectPtr<UBlueprint> Blueprint = ViewModel->GetSelectedBlueprint();
	const FString ParentClassModuleName = FGBAScaffoldUtils::GetContainingModuleName(ParentClassInfo.BaseClass);

	ViewModel->AddRequiredModuleDependency(ParentClassModuleName, LOCTEXT("RequiredParentClassModule", "Parent Class"));

	if (Blueprint.IsValid())
	{
		const bool bHasClampedProperties = FGBAHeaderViewListItem::IsUsingClampedAttributeData(Blueprint->SkeletonGeneratedClass);
		if (bHasClampedProperties)
		{
			ViewModel->AddRequiredModuleDependency(TEXT("BlueprintAttributes"), LOCTEXT("RequiredClampedStructModule", "Using FGBAGameplayClampedAttributeData struct"));
		}
	}
	
	ViewModel->UpdateInputValidity();	
}

#undef LOCTEXT_NAMESPACE
