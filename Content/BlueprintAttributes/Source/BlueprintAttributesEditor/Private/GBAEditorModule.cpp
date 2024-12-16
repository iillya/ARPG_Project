// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAEditorModule.h"

#include "AssetToolsModule.h"
#include "GBAConstants.h"
#include "GBAEditorLog.h"
#include "PropertyEditorModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetTypes/GBAAssetTypeActions_AttributeSet.h"
#include "AttributeReferenceViewer/GBAAttributeListReferenceViewer.h"
#include "Details/GBAAttributeSetDetails.h"
#include "Details/GBAGameplayAttributeDataClampedDetails.h"
#include "Details/GBAGameplayAttributeDataDetails.h"
#include "Details/GBAGameplayAttributePropertyDetails.h"
#include "Editor/GBAGraphPanelPinFactory.h"
#include "Editor/Slate/SGBANewDataTableWindowContent.h"
#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IMainFrameModule.h"
#include "Misc/EngineVersionComparison.h"

#define LOCTEXT_NAMESPACE "FGBAEditorModule"

void FGBAEditorModule::StartupModule()
{
	// Module is set to kick in PreLoadingScreen
	// so that it starts right before GameplayAbilitiesEditorModule (which is PreDefault)
	//
	// Mainly to hook in our own GraphPanelPinFactory to return our version of SGraphPing widget, since we can't really unregister
	// the visual pin factory of Gameplay Abilities Editor module from outside modules.
	//
	// Registering ours earlier so that editor considers it before evaluating the default one (we need to expose Attributes added in BP for K2 Nodes)
	//
	GBA_EDITOR_LOG(Verbose, TEXT("FGBAEditorModule::StartupModule"))

	RegisterConsoleCommands();

	// Every other logic that would have happened in here is delayed to OnPostEngineInit
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FGBAEditorModule::OnPostEngineInit);

	// Register factories for pins and nodes
	//
	// That is for K2 nodes with FGameplayAttribute pins, like GetFloatAttributeBase from ASC
	GameplayAbilitiesGraphPanelPinFactory = MakeShared<FGBAGraphPanelPinFactory>();
	FEdGraphUtilities::RegisterVisualPinFactory(GameplayAbilitiesGraphPanelPinFactory);
}

void FGBAEditorModule::ShutdownModule()
{
	GBA_EDITOR_LOG(Verbose, TEXT("FGBAEditorModule::ShutdownModule"))

	FCoreDelegates::OnPostEngineInit.RemoveAll(this);
	
	UnregisterConsoleCommands();

	// Unregister customizations
	if (FModuleManager::Get().IsModuleLoaded(TEXT("PropertyEditor")))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("GameplayAttribute"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("GameplayAttributeData"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("GBAGameplayClampedAttributeData"));

		PropertyModule.UnregisterCustomClassLayout(TEXT("GBAAttributeSetBlueprintBase"));
	}

	// Unregister asset type actions
	if (FModuleManager::Get().IsModuleLoaded(TEXT("AssetTools")))
	{
		IAssetTools& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();
		for (TSharedPtr<IAssetTypeActions>& AssetTypeAction : CreatedAssetTypeActions)
		{
			if (AssetTypeAction.IsValid())
			{
				AssetToolsModule.UnregisterAssetTypeActions(AssetTypeAction.ToSharedRef());
			}
		}
	}
	CreatedAssetTypeActions.Empty();

	// Unregister graph factories
	if (GameplayAbilitiesGraphPanelPinFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualPinFactory(GameplayAbilitiesGraphPanelPinFactory);
		GameplayAbilitiesGraphPanelPinFactory.Reset();
	}
}

void FGBAEditorModule::RegisterConsoleCommands()
{
	ConsoleCommands.Add(IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("GBA.Test"),
		TEXT("Display Attribute references dialog"),
		FConsoleCommandWithArgsDelegate::CreateRaw(this, &FGBAEditorModule::ExecuteShowGameplayAttributeReferencesWindow),
		ECVF_Default
	));
}

void FGBAEditorModule::UnregisterConsoleCommands()
{
	for (IConsoleCommand* ConsoleCommand : ConsoleCommands)
	{
		IConsoleManager::Get().UnregisterConsoleObject(ConsoleCommand);
	}

	ConsoleCommands.Empty();
}

void FGBAEditorModule::ExecuteShowGameplayAttributeReferencesWindow(const TArray<FString>& InArgs)
{
	const FString Argv = FString::Join(InArgs, TEXT(" "));

	GBA_EDITOR_NS_LOG(Verbose, TEXT("Start command - Search for %s"), *Argv)
	
	const FVector2D WindowSize(800, 800);

	AttributeListReferenceViewerWidget = SNew(SGBAAttributeListReferenceViewer);
	const FText Title = LOCTEXT("AttributeListReferenceViewer_Title", "Attribute Reference Viewer");

	AttributeListReferenceViewerWindow = SNew(SWindow)
		.Title(Title)
		.HasCloseButton(true)
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		.AutoCenter(EAutoCenter::PreferredWorkArea)
		.ClientSize(WindowSize)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.FillHeight(1)
				[
					AttributeListReferenceViewerWidget.ToSharedRef()
				]
			]
		];

	// NOTE: FGlobalTabmanager::Get()-> is actually dereferencing a SharedReference, not a SharedPtr, so it cannot be null.
	if (FGlobalTabmanager::Get()->GetRootWindow().IsValid())
	{
		FSlateApplication::Get().AddWindowAsNativeChild(AttributeListReferenceViewerWindow.ToSharedRef(), FGlobalTabmanager::Get()->GetRootWindow().ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(AttributeListReferenceViewerWindow.ToSharedRef());
	}
	
	check (AttributeListReferenceViewerWidget.IsValid());

	// Set focus to the search box on creation
	FSlateApplication::Get().SetKeyboardFocus(AttributeListReferenceViewerWidget->GetWidgetToFocusOnOpen());
	FSlateApplication::Get().SetUserFocus(0, AttributeListReferenceViewerWidget->GetWidgetToFocusOnOpen());
}

void FGBAEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

void FGBAEditorModule::OnPostEngineInit()
{
	// Detail Customizations
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

		// Unregister GAS default customization for Gameplay Attributes and Sets
		PropertyModule.UnregisterCustomClassLayout(TEXT("AttributeSet"));
		PropertyModule.UnregisterCustomPropertyTypeLayout("GameplayAttribute");

		// And register our own customizations
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("GameplayAttribute"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGBAGameplayAttributePropertyDetails::MakeInstance));

		// Note: We still need a customization, namely because I'd like to keep the customization for the header and
		// support for compact view, but base / current value handling can now be removed
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("GameplayAttributeData"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGBAGameplayAttributeDataDetails::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("GBAGameplayClampedAttributeData"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGBAGameplayAttributeDataClampedDetails::MakeInstance));
		
		PropertyModule.RegisterCustomClassLayout(TEXT("GBAAttributeSetBlueprintBase"), FOnGetDetailCustomizationInstance::CreateStatic(&FGBAAttributeSetDetails::MakeInstance));

		// Make the Base and CurrentValue editable in editor, without having to rely on heavy details customization
		SetupGameplayAttributesPropertyFlags();
	}

	// Asset Types
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();

		constexpr EAssetTypeCategories::Type AssetCategory = EAssetTypeCategories::Gameplay;
		GBA_EDITOR_LOG(Verbose, TEXT("FGBAEditorModule::RegisterAssetTypeAction FGBAAssetTypeActions_AttributeSet"))
		RegisterAssetTypeAction(AssetTools, MakeShared<FGBAAssetTypeActions_AttributeSet>(AssetCategory));
	}
}

void FGBAEditorModule::SetupGameplayAttributesPropertyFlags()
{
	// Make the Base and CurrentValue editable in editor, without having to rely on heavy details customization
	// Thanks to @benw on discord for teaching me this cool trick, and the bug report.

	// We still continue using a details customization though to handle things like compact view, header row tweaks, etc.
	const UStruct* AttributeDataStruct = FGameplayAttributeData::StaticStruct();
	check(AttributeDataStruct);
	
	if (FProperty* BaseValueProperty = AttributeDataStruct->FindPropertyByName(GBA::Constants::BaseValuePropertyName))
	{
		// Mimics EditDefaultsOnly UPROPERTY specifier: https://github.com/EpicGames/UnrealEngine/blob/5.4.2-release/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs#L52
		BaseValueProperty->SetPropertyFlags(CPF_Edit | CPF_DisableEditOnInstance);
	}

	if (FProperty* CurrentValueProperty = AttributeDataStruct->FindPropertyByName(GBA::Constants::CurrentValuePropertyName))
	{
		// Mimics VisibleDefaultsOnly UPROPERTY specifier: https://github.com/EpicGames/UnrealEngine/blob/5.4.2-release/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs#L88
		CurrentValueProperty->SetPropertyFlags(CPF_Edit | CPF_EditConst | CPF_DisableEditOnInstance);
	}
}

void FGBAEditorModule::PreloadAssetsByClass(UClass* InClass) const
{
	GBA_EDITOR_LOG(Verbose, TEXT("FGBAEditorModule::PreloadAssetsByClass - Preloading assets with class %s"), *GetNameSafe(InClass))
	if (!InClass)
	{
		return;
	}

	const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();

	TArray<FAssetData> Assets;
#if UE_VERSION_NEWER_THAN(5, 1, -1)
	AssetRegistry.GetAssetsByClass(InClass->GetClassPathName(), Assets, true);
#else
	AssetRegistry.GetAssetsByClass(InClass->GetFName(), Assets, true);
#endif

	GBA_EDITOR_LOG(Verbose, TEXT("FGBAEditorModule::PreloadAssetsByClass - Preloading %d assets with class %s"), Assets.Num(), *GetNameSafe(InClass))
	for (const FAssetData& Asset : Assets)
	{
		GBA_EDITOR_LOG(Verbose, TEXT("\nFGBAEditorModule::PreloadAssetsByClass Preload asset PackageName: %s"), *Asset.PackageName.ToString())
		if (!Asset.IsAssetLoaded())
		{
			Asset.GetAsset();
		}
	}
}

TSharedRef<SWindow> FGBAEditorModule::CreateDataTableWindow(const TWeakObjectPtr<UBlueprint>& InBlueprint, const FGBADataTableWindowArgs& InArgs) const
{
	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(InArgs.Title)
		.ClientSize(InArgs.Size)
		.SizingRule(InArgs.SizingRule)
		.MinWidth(InArgs.Size.X / 2)
		.MinHeight(InArgs.Size.Y / 2)
		.SupportsMinimize(InArgs.bSupportsMinimize)
		.SupportsMaximize(InArgs.bSupportsMaximize);

	const TSharedRef<SGBANewDataTableWindowContent> Content = SNew(SGBANewDataTableWindowContent, InBlueprint);
	Window->SetContent(Content);

	TSharedPtr<SWindow> ParentWindow;
	if (FModuleManager::Get().IsModuleLoaded(TEXT("MainFrame")))
	{
		const IMainFrameModule& MainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
		ParentWindow = MainFrame.GetParentWindow();
	}

	if (InArgs.bIsModal)
	{
		FSlateApplication::Get().AddModalWindow(Window, ParentWindow, false);
	}
	else if (ParentWindow.IsValid())
	{
		FSlateApplication::Get().AddWindowAsNativeChild(Window, ParentWindow.ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(Window);
	}

	return Window;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGBAEditorModule, BlueprintAttributesEditor)
