// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "SGBAClassInfo.h"

#include "AbilitySystemTestAttributeSet.h"
#include "AttributeSet.h"
#include "ClassViewerFilter.h"
#include "DesktopPlatformModule.h"
#include "GameProjectUtils.h"
#include "ModuleDescriptor.h"
#include "SlateOptMacros.h"
#include "Editor/ClassViewer/Public/ClassViewerModule.h"
#include "Misc/App.h"
#include "Models/GBAAttributeSetWizardViewModel.h"
#include "Styling/GBAAppStyle.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SSegmentedControl.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SGridPanel.h"

#define LOCTEXT_NAMESPACE "SGBABlueprintHeaderView"

FString SGBAClassInfo::LastSelectedModuleName = TEXT("");

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

// ReSharper disable once CppParameterNeverUsed
void SGBAClassInfo::Construct(const FArguments& InArgs, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel)
{
	constexpr float EditableTextHeight = 26.0f;

	ViewModel = InViewModel;
	check(ViewModel.IsValid());

	InitAvailableModules();
	const TSharedPtr<FModuleContextInfo> SelectedModuleInfo = InitSelectedModuleInfo();
	ViewModel->SetSelectedModuleInfo(SelectedModuleInfo);
	if (SelectedModuleInfo.IsValid())
	{
		ViewModel->SetNewClassPath(SelectedModuleInfo->ModuleSourcePath / TEXT("Public"));
		ViewModel->SetSelectedClassPath(TEXT(""));
	}

	// Will update ClassVisibility correctly
	ViewModel->UpdateInputValidity();

	ChildSlot
	[
		SNew(SVerticalBox)

		// Page description and view options
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0, 10)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("ClassInfo_Description_Native", "This will add a C++ header and source code file to your game project."))
		]

		// Properties
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FGBAAppStyle::GetBrush("DetailsView.CategoryTop"))
			.BorderBackgroundColor(FLinearColor(0.6f, 0.6f, 0.6f, 1.0f))
			.Padding(FMargin(6.0f, 4.0f, 7.0f, 4.0f))
			[
				SNew(SVerticalBox)

				+SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0)
				[
					SNew(SGridPanel)
					.FillColumn(1, 1.0f)
					// Class type label

					+SGridPanel::Slot(0, 0)
					.VAlign(VAlign_Center)
					.Padding(0, 0, 12, 0)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("ClassTypeLabel", "Class Type"))
					]

					+SGridPanel::Slot(1, 0)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Left)
					.Padding(2.0f)
					[
						SNew(SHorizontalBox)

						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SSegmentedControl<GameProjectUtils::EClassLocation>)
							.OnValueChanged(this, &SGBAClassInfo::OnClassLocationChanged)
							.Value(this, &SGBAClassInfo::GetClassLocation)
							+SSegmentedControl<GameProjectUtils::EClassLocation>::Slot(GameProjectUtils::EClassLocation::Public)
							.Text(LOCTEXT("Public", "Public"))
							.ToolTip(LOCTEXT("ClassLocation_Public", "A public class can be included and used inside other modules in addition to the module it resides in"))
							+SSegmentedControl<GameProjectUtils::EClassLocation>::Slot(GameProjectUtils::EClassLocation::Private)
							.Text(LOCTEXT("Private", "Private"))
							.ToolTip(LOCTEXT("ClassLocation_Private", "A private class can only be included and used within the module it resides in"))
						]

						+SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Left)
						.Padding(FMargin(8.f))
						[
							SNew(STextBlock)
							.Text(LOCTEXT("ClassPickerLabel", "Parent Class:"))
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Left)
						[
							SNew(SSpacer)
							.Size(FVector2D(8.f))
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Left)
						[
							SNew(SBox)
							.WidthOverride(400.0f)
							[
								SAssignNew(ParentClassPickerComboButton, SComboButton)
								.OnGetMenuContent(this, &SGBAClassInfo::GetClassPickerMenuContent)
								.ButtonContent()
								[
									SNew(STextBlock)
									.Text(this, &SGBAClassInfo::GetClassPickerText, false)
									.ToolTipText(this, &SGBAClassInfo::GetClassPickerText, true)
								]
							]
						]
					]

					// Name label
					+SGridPanel::Slot(0, 1)
					.VAlign(VAlign_Center)
					.Padding(0, 0, 12, 0)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("NameLabel", "Name"))
						.ToolTipText(LOCTEXT("NameDescription", "This is the name of the class and header / source filenames"))
					]

					// Name edit box
					+SGridPanel::Slot(1, 1)
					.Padding(0.0f, 3.0f)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.HeightOverride(EditableTextHeight)
						[
							SNew(SHorizontalBox)

							+SHorizontalBox::Slot()
							.FillWidth(.7f)
							[
								SAssignNew(ClassNameEditBox, SEditableTextBox)
								.Text(this, &SGBAClassInfo::OnGetClassNameText)
								.OnTextChanged(this, &SGBAClassInfo::OnClassNameTextChanged)
								.ToolTipText(LOCTEXT("NameDescription", "This is the name of the class and header / source filenames"))
							]

							+SHorizontalBox::Slot()
							.AutoWidth()
							.Padding(6.0f, 0.0f, 0.0f, 0.0f)
							[
								SAssignNew(AvailableModulesCombo, SComboBox<TSharedPtr<FModuleContextInfo>>)
								.ToolTipText(LOCTEXT("ModuleComboToolTip", "Choose the target module for your new class"))
								.OptionsSource(&AvailableModules)
								.InitiallySelectedItem(SelectedModuleInfo)
								.OnSelectionChanged(this, &SGBAClassInfo::HandleSelectedModuleComboBoxSelectionChanged)
								.OnGenerateWidget(this, &SGBAClassInfo::MakeWidgetForSelectedModuleCombo)
								[
									SNew(STextBlock)
									.Text(this, &SGBAClassInfo::GetSelectedModuleComboText)
								]
							]
						]
					]

					// Path label
					+SGridPanel::Slot(0, 2)
					.VAlign(VAlign_Center)
					.Padding(0, 0, 12, 0)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("PathLabel", "Relative Path"))
						.ToolTipText(LOCTEXT("NameDescription", "This is the relative path beneath the target module source path"))
					]

					// Path edit box
					+SGridPanel::Slot(1, 2)
					.Padding(0.0f, 3.0f)
					.VAlign(VAlign_Center)
					[
						SNew(SVerticalBox)

						// Native C++ path
						+SVerticalBox::Slot()
						.Padding(0)
						.AutoHeight()
						[
							SNew(SBox)
							.HeightOverride(EditableTextHeight)
							[
								SNew(SHorizontalBox)

								+SHorizontalBox::Slot()
								.FillWidth(1.0f)
								[
									SNew(SEditableTextBox)
									.Text(this, &SGBAClassInfo::OnGetClassPathText)
									.OnTextChanged(this, &SGBAClassInfo::OnClassPathTextChanged)
									.IsEnabled(this, &SGBAClassInfo::IsClassPathTextEnabled)
									.ToolTipText(LOCTEXT("NameDescription", "This is the relative path beneath the target module source path"))
								]

								+SHorizontalBox::Slot()
								.AutoWidth()
								.Padding(6.0f, 1.0f, 0.0f, 0.0f)
								[
									SNew(SButton)
									.VAlign(VAlign_Center)
									.ButtonStyle(FAppStyle::Get(), "SimpleButton")
									.OnClicked(this, &SGBAClassInfo::HandleChooseFolderButtonClicked)
									[
										SNew(SImage)
										.Image(FAppStyle::Get().GetBrush("Icons.FolderClosed"))
										.ColorAndOpacity(FSlateColor::UseForeground())
									]
								]
							]
						]
					]

					// Header output label
					+SGridPanel::Slot(0, 3)
					.VAlign(VAlign_Center)
					.Padding(0, 0, 12, 0)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HeaderFileLabel", "Header File"))
					]

					// Header output text
					+SGridPanel::Slot(1, 3)
					.Padding(0.0f, 3.0f)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.VAlign(VAlign_Center)
						.HeightOverride(EditableTextHeight)
						[
							SNew(STextBlock)
							.Text(this, &SGBAClassInfo::OnGetClassHeaderFileText)
						]
					]

					// Source output label
					+SGridPanel::Slot(0, 4)
					.VAlign(VAlign_Center)
					.Padding(0, 0, 12, 0)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("SourceFileLabel", "Source File"))
					]

					// Source output text
					+SGridPanel::Slot(1, 4)
					.Padding(0.0f, 3.0f)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.VAlign(VAlign_Center)
						.HeightOverride(EditableTextHeight)
						[
							SNew(STextBlock)
							.Text(this, &SGBAClassInfo::OnGetClassSourceFileText)
						]
					]
				]
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SGBAClassInfo::InitAvailableModules()
{
	TArray<FModuleContextInfo> CurrentModules = GameProjectUtils::GetCurrentProjectModules();
	// This should never happen since GetCurrentProjectModules is supposed to add a dummy runtime module if the project currently has no modules
	check(CurrentModules.Num());
	Algo::SortBy(CurrentModules, &FModuleContextInfo::ModuleName);

	TArray<FModuleContextInfo> CurrentPluginModules = GameProjectUtils::GetCurrentProjectPluginModules();
	Algo::SortBy(CurrentPluginModules, &FModuleContextInfo::ModuleName);
	CurrentModules.Append(CurrentPluginModules);

	AvailableModules.Reserve(CurrentModules.Num());
	for (const FModuleContextInfo& ModuleInfo : CurrentModules)
	{
		AvailableModules.Emplace(MakeShareable(new FModuleContextInfo(ModuleInfo)));
	}
}

TSharedPtr<FModuleContextInfo> SGBAClassInfo::InitSelectedModuleInfo()
{
	const FString ProjectName = FApp::GetProjectName();

	// Find best suited module based on simple fallback in this order:
	// Main project module, a runtime module
	TSharedPtr<FModuleContextInfo> ProjectModule;
	TSharedPtr<FModuleContextInfo> RuntimeModule;
	TSharedPtr<FModuleContextInfo> LastSelectedModule;

	for (const TSharedPtr<FModuleContextInfo>& AvailableModule : AvailableModules)
	{
		if (AvailableModule->ModuleName == ProjectName)
		{
			ProjectModule = AvailableModule;
		}

		if (AvailableModule->ModuleType == EHostType::Runtime)
		{
			RuntimeModule = AvailableModule;
		}

		if (AvailableModule->ModuleName == LastSelectedModuleName)
		{
			LastSelectedModule = AvailableModule;
		}
	}

	TSharedPtr<FModuleContextInfo> ModuleInfo;
	if (LastSelectedModule.IsValid())
	{
		// use the project module we found
		ModuleInfo = LastSelectedModule;
	}
	else if (ProjectModule.IsValid())
	{
		// use the project module we found
		ModuleInfo = ProjectModule;
	}
	else if (RuntimeModule.IsValid())
	{
		// use the first runtime module we found
		ModuleInfo = RuntimeModule;
	}
	else
	{
		// default to just the first module
		ModuleInfo = AvailableModules[0];
	}

	return ModuleInfo;
}

GameProjectUtils::EClassLocation SGBAClassInfo::GetClassLocation() const
{
	check(ViewModel.IsValid());
	return ViewModel->GetClassLocation();
}

void SGBAClassInfo::OnClassLocationChanged(const GameProjectUtils::EClassLocation InLocation) const
{
	check(ViewModel.IsValid());
	ViewModel->SetNewClassPath(CalculateNewClassPath(InLocation, ViewModel->GetNewClassPath()));

	// Will update ClassVisibility correctly
	ViewModel->UpdateInputValidity();
}

FText SGBAClassInfo::OnGetClassNameText() const
{
	check(ViewModel.IsValid());
	return FText::FromString(ViewModel->GetNewClassName());
}

void SGBAClassInfo::OnClassNameTextChanged(const FText& InNewText) const
{
	check(ViewModel.IsValid());
	ViewModel->SetNewClassName(InNewText.ToString());
	ViewModel->UpdateInputValidity();
}

FText SGBAClassInfo::GetSelectedModuleComboText() const
{
	check(ViewModel.IsValid());

	const TSharedPtr<FModuleContextInfo> SelectedModuleInfo = ViewModel->GetSelectedModuleInfo();
	check(SelectedModuleInfo.IsValid());
	
	FFormatNamedArguments Args;
	Args.Add(TEXT("ModuleName"), FText::FromString(SelectedModuleInfo->ModuleName));
	Args.Add(TEXT("ModuleType"), FText::FromString(EHostType::ToString(SelectedModuleInfo->ModuleType)));
	return FText::Format(LOCTEXT("ModuleComboEntry", "{ModuleName} ({ModuleType})"), Args);
}

// ReSharper disable once CppParameterNeverUsed
void SGBAClassInfo::HandleSelectedModuleComboBoxSelectionChanged(const TSharedPtr<FModuleContextInfo> InSelectedModuleInfo, ESelectInfo::Type InSelectInfo) const
{
	check(ViewModel.IsValid());

	const TSharedPtr<FModuleContextInfo> SelectedModuleInfo = ViewModel->GetSelectedModuleInfo();
	check(SelectedModuleInfo.IsValid());
	
	const FString& OldModulePath = SelectedModuleInfo->ModuleSourcePath;
	const FString& NewModulePath = InSelectedModuleInfo->ModuleSourcePath;

	ViewModel->SetSelectedModuleInfo(InSelectedModuleInfo);
	LastSelectedModuleName = InSelectedModuleInfo->ModuleName;

	// Update the class path to be rooted to the new module location
	const FString AbsoluteClassPath = FPaths::ConvertRelativePathToFull(ViewModel->GetNewClassPath()) / TEXT(""); // Ensure trailing /
	if (AbsoluteClassPath.StartsWith(OldModulePath))
	{
		ViewModel->SetNewClassPath(AbsoluteClassPath.Replace(*OldModulePath, *NewModulePath));
	}
	else
	{
		// Can happen if user selected an invalid folder (not within any project modules source)
		const FString SelectedAbsoluteClassPath = SelectedModuleInfo->ModuleSourcePath / ViewModel->GetSelectedClassPath();
		ViewModel->SetNewClassPath(CalculateNewClassPath(GameProjectUtils::EClassLocation::Public, SelectedAbsoluteClassPath));
	}

	ViewModel->UpdateInputValidity();
}

TSharedRef<SWidget> SGBAClassInfo::MakeWidgetForSelectedModuleCombo(const TSharedPtr<FModuleContextInfo> InValue) const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("ModuleName"), FText::FromString(InValue->ModuleName));
	Args.Add(TEXT("ModuleType"), FText::FromString(EHostType::ToString(InValue->ModuleType)));
	return SNew(STextBlock)
		.Text(FText::Format(LOCTEXT("ModuleComboEntry", "{ModuleName} ({ModuleType})"), Args));
}

FText SGBAClassInfo::OnGetClassPathText() const
{
	check(ViewModel.IsValid());
	return FText::FromString(ViewModel->GetSelectedClassPath());
}

bool SGBAClassInfo::IsClassPathTextEnabled() const
{
	check(ViewModel.IsValid());
	// For now, just enable / disable based on input validity
	return ViewModel->IsLastInputValidityCheckSuccessful();
}

void SGBAClassInfo::OnClassPathTextChanged(const FText& InNewText)
{
	check(ViewModel.IsValid());
	
	const TSharedPtr<FModuleContextInfo> SelectedModuleInfo = ViewModel->GetSelectedModuleInfo();

	const FString NewSelectedClassPath = InNewText.ToString();

	if (SelectedModuleInfo.IsValid())
	{
		const FString AbsoluteClassPath = SelectedModuleInfo->ModuleSourcePath / NewSelectedClassPath;
		const FString NewPath = CalculateNewClassPath(ViewModel->GetClassLocation(), AbsoluteClassPath);

		// Prevent displaying header / source file path in Engine/Binaries in case NewClassPath is empty (CalculateNewClassPath failed to compute a valid path)
		// Can happen if user has selected a folder (with the choose folder button) outside of the target module source path
		if (!NewPath.IsEmpty())
		{
			ViewModel->SetNewClassPath(NewPath);
		}
	}

	// If the user has selected a path which matches the root of a known module, then update our selected module to be that module
	for (const TSharedPtr<FModuleContextInfo>& AvailableModule : AvailableModules)
	{
		if (ViewModel->GetNewClassPath().StartsWith(AvailableModule->ModuleSourcePath))
		{
			ViewModel->SetSelectedModuleInfo(AvailableModule);
			AvailableModulesCombo->SetSelectedItem(AvailableModule);
			break;
		}
	}

	ViewModel->SetSelectedClassPath(NewSelectedClassPath);

	ViewModel->UpdateInputValidity();
}

FString SGBAClassInfo::CalculateNewClassPath(const GameProjectUtils::EClassLocation InLocation, const FString& InNewClassPath) const
{
	check(ViewModel.IsValid());
	
	const TSharedPtr<FModuleContextInfo> SelectedModuleInfo = ViewModel->GetSelectedModuleInfo();
	check(SelectedModuleInfo.IsValid());

	const FString AbsoluteClassPath = FPaths::ConvertRelativePathToFull(InNewClassPath) / ""; // Ensure trailing /

	GameProjectUtils::EClassLocation TmpClassLocation = GameProjectUtils::EClassLocation::UserDefined;
	GameProjectUtils::GetClassLocation(AbsoluteClassPath, *SelectedModuleInfo, TmpClassLocation);

	const FString RootPath = SelectedModuleInfo->ModuleSourcePath;
	const FString PublicPath = RootPath / "Public" / ""; // Ensure trailing /
	const FString PrivatePath = RootPath / "Private" / ""; // Ensure trailing /

	FString Result;
	// Update the class path to be rooted to the Public or Private folder based on InVisibility
	switch (InLocation)
	{
	case GameProjectUtils::EClassLocation::Public:
		if (AbsoluteClassPath.StartsWith(PrivatePath))
		{
			Result = AbsoluteClassPath.Replace(*PrivatePath, *PublicPath);
		}
		else if (AbsoluteClassPath.StartsWith(RootPath))
		{
			Result = AbsoluteClassPath.Replace(*RootPath, *PublicPath);
		}
		else
		{
			Result = PublicPath;
		}
		break;

	case GameProjectUtils::EClassLocation::Private:
		if (AbsoluteClassPath.StartsWith(PublicPath))
		{
			Result = AbsoluteClassPath.Replace(*PublicPath, *PrivatePath);
		}
		else if (AbsoluteClassPath.StartsWith(RootPath))
		{
			Result = AbsoluteClassPath.Replace(*RootPath, *PrivatePath);
		}
		else
		{
			Result = PrivatePath;
		}
		break;

	default:
		break;
	}

	return Result;
}

FText SGBAClassInfo::OnGetClassHeaderFileText() const
{
	check(ViewModel.IsValid());
	return FText::FromString(ViewModel->GetCalculatedClassHeaderName());
}

FText SGBAClassInfo::OnGetClassSourceFileText() const
{
	check(ViewModel.IsValid());
	return FText::FromString(ViewModel->GetCalculatedClassSourceName());
}

FReply SGBAClassInfo::HandleChooseFolderButtonClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		return FReply::Handled();
	}

	check(ViewModel.IsValid());
	
	const TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());
	const void* ParentWindowWindowHandle = ParentWindow.IsValid() ? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;

	FString FolderName;
	const FString Title = LOCTEXT("NewClassBrowseTitle", "Choose a source location").ToString();

	const bool bFolderSelected = DesktopPlatform->OpenDirectoryDialog(ParentWindowWindowHandle, Title, ViewModel->GetNewClassPath(), FolderName);

	if (bFolderSelected)
	{
		if (!FolderName.EndsWith(TEXT("/")))
		{
			FolderName += TEXT("/");
		}

		ViewModel->SetNewClassPath(FolderName);

		const FString NewClassPath = ViewModel->GetNewClassPath();

		// If the user has selected a path which matches the root of a known module, then update our selected module to be that module
		for (const TSharedPtr<FModuleContextInfo>& AvailableModule : AvailableModules)
		{
			if (NewClassPath.StartsWith(AvailableModule->ModuleSourcePath))
			{
				ViewModel->SetSelectedModuleInfo(AvailableModule);
				// AvailableModulesCombo->SetSelectedItem(AvailableModule);

				// Update Path field too if we match a valid module
				const FString RootPath = AvailableModule->ModuleSourcePath;
				const FString PublicPath = RootPath / TEXT("Public") / TEXT(""); // Ensure trailing /
				const FString PrivatePath = RootPath / TEXT("Private") / TEXT(""); // Ensure trailing /

				if (NewClassPath.StartsWith(PublicPath))
				{
					ViewModel->SetSelectedClassPath(NewClassPath.Replace(*PublicPath, TEXT("")));
				}
				else if (NewClassPath.StartsWith(PrivatePath))
				{
					ViewModel->SetSelectedClassPath(NewClassPath.Replace(*PrivatePath, TEXT("")));
				}
				else
				{
					// Neither a public or private path, fallback to public behavior
					// Can happen if user chooses an invalid path and then the root path of a module (before Public / Private folders)
					//
					// ViewModel->SetSelectedClassPath(NewClassPath.Replace(*PublicPath, TEXT("")));
				}

				break;
			}
		}

		ViewModel->UpdateInputValidity();
	}

	return FReply::Handled();
}

FText SGBAClassInfo::GetClassPickerText(const bool bIsTooltipText) const
{
	check(ViewModel.IsValid());

	const FNewClassInfo ParentClassInfo = ViewModel->GetParentClassInfo();
	if (!ParentClassInfo.IsSet())
	{
		return LOCTEXT("ClassPickerPickParentClass", "Select Parent Class");
	}

	if (!bIsTooltipText)
	{
		// not for tooltip, only show class name
		return FText::FromString(ParentClassInfo.BaseClass->GetName());
	}

	FString IncludePath;
	if (ParentClassInfo.BaseClass && ParentClassInfo.BaseClass->HasMetaData(TEXT("IncludePath")))
	{
		IncludePath = ParentClassInfo.BaseClass->GetMetaData(TEXT("IncludePath"));
	}

	// Figure out module name
	FString ModuleName;
	const FString ScriptText = TEXT("/Script/");
	const UPackage* Outer = ParentClassInfo.BaseClass->GetOutermost();
	if (Outer && Outer->GetName().StartsWith(ScriptText))
	{
		ModuleName = *Outer->GetName().RightChop(ScriptText.Len());
	}

	FText Result = FText::Format(
		LOCTEXT("ClassPickerText", "{0} ({1} from {2} module)"),
		FText::FromString(ParentClassInfo.BaseClass->GetName()),
		FText::FromString(IncludePath),
		FText::FromString(ModuleName)
	);

	return Result;
}

class FGBABlueprintParentFilter : public IClassViewerFilter
{
public:
	/** All children of these classes will be included unless filtered out by another setting. */
	TSet<const UClass*> AllowedChildrenOfClasses;

	explicit FGBABlueprintParentFilter(const TSet<const UClass*>& InAllowedChildrenOfClasses)
		: AllowedChildrenOfClasses(InAllowedChildrenOfClasses)
	{
	}

	explicit FGBABlueprintParentFilter(const UClass* InAllowedClass)
	{
		AllowedChildrenOfClasses.Add(InAllowedClass);
	}

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, const TSharedRef<FClassViewerFilterFuncs> InFilterFunctions) override
	{
		if (!InClass)
		{
			return false;
		}

		const bool bIsAllowedChildClass = IsAllowedChildClass(InClass);
		if (!bIsAllowedChildClass)
		{
			return false;
		}

		// Filter out Gameplay Abilities internal Test Attribute Set
		if (InClass == UAbilitySystemTestAttributeSet::StaticClass())
		{
			return false;
		}

		const bool bIsNativeClass = IsNativeClass(InClass);
		
		// Figure out if it is a native class
		if (!bIsNativeClass)
		{
			return false;
		}

		return true;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, const TSharedRef<FClassViewerFilterFuncs> InFilterFunctions) override
	{
		return InFilterFunctions->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}

	static bool IsNativeClass(const UClass* InClass)
	{
		return !InClass->HasAnyClassFlags(CLASS_Deprecated) && InClass->HasAnyClassFlags(CLASS_Native);
	}

	bool IsAllowedChildClass(const UClass* InClass)
	{
		check(InClass);
		for (const UClass* BaseClass : AllowedChildrenOfClasses)
		{
			if (!BaseClass)
			{
				continue;
			}

			if (InClass->IsChildOf(BaseClass))
			{
				return true;
			}
		}
		
		return false;
	}
};

TSharedRef<SWidget> SGBAClassInfo::GetClassPickerMenuContent()
{
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	FClassViewerInitializationOptions Options;

	Options.ClassFilters.Add(MakeShared<FGBABlueprintParentFilter>(UAttributeSet::StaticClass()));
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.DisplayMode = EClassViewerDisplayMode::TreeView;
	Options.bShowObjectRootClass = false;
	Options.bShowNoneOption = false;
	Options.bExpandAllNodes = true;

	// This will allow unloaded blueprints to be shown.
	Options.bShowUnloadedBlueprints = false;
	Options.bIsBlueprintBaseOnly = false;

	return SNew(SBox)
		.HeightOverride(500.f)
		[
			ClassViewerModule.CreateClassViewer(
				Options,
				FOnClassPicked::CreateSP(this, &SGBAClassInfo::OnParentClassSelected)
			)
		];
}

void SGBAClassInfo::OnParentClassSelected(UClass* InParentClass) const
{
	check(ViewModel.IsValid());
	
	if (ParentClassPickerComboButton.IsValid())
	{
		ParentClassPickerComboButton->SetIsOpen(false);
	}

	if (!InParentClass)
	{
		ViewModel->SetParentClassInfo(FNewClassInfo());
		return;
	}

	ViewModel->SetParentClassInfo(FNewClassInfo(InParentClass));
}

#undef LOCTEXT_NAMESPACE
