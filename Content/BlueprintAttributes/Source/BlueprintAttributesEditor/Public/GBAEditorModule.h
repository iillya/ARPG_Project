// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGBAEditorModule.h"

class SGBAAttributeListReferenceViewer;
struct FGraphPanelPinFactory;
class IAssetTypeActions;

class FGBAEditorModule : public IGBAEditorModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<IConsoleCommand*> ConsoleCommands;
	TSharedPtr<SGBAAttributeListReferenceViewer> AttributeListReferenceViewerWidget;
	TSharedPtr<SWindow> AttributeListReferenceViewerWindow;

	void RegisterConsoleCommands();
	void UnregisterConsoleCommands();
	
	void ExecuteShowGameplayAttributeReferencesWindow(const TArray<FString>& InArgs);
	
	/** All created asset type actions. Cached here so that we can unregister it during shutdown. */
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
	
	/** Pin factory for gameplay abilities; Cached so it can be unregistered */
	TSharedPtr<FGraphPanelPinFactory> GameplayAbilitiesGraphPanelPinFactory;
	
	void RegisterAssetTypeAction(class IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	
	void OnPostEngineInit();

	/** Make the Base and CurrentValue editable in editor, without having to rely on heavy details customization */
	static void SetupGameplayAttributesPropertyFlags();

	//~ Begin IGBAEditorModule
	virtual void PreloadAssetsByClass(UClass* InClass) const override;
	virtual TSharedRef<SWindow> CreateDataTableWindow(const TWeakObjectPtr<UBlueprint>& InBlueprint, const FGBADataTableWindowArgs& InArgs) const override;
	//~ End IGBAEditorModule
};
