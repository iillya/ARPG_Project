// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGBAScaffoldModule.h"

class SWindow;
class FExtender;
struct FTableRowStyle;
struct FTextBlockStyle;

class FGBAScaffoldModule : public IGBAScaffoldModule
{
public:
	/** Text style for the Header View Output */
	static FTextBlockStyle HeaderViewTextStyle;

	/** TableRow style for the Header View Output */
	static FTableRowStyle HeaderViewTableRowStyle;

	//~ Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface
	
	/** Returns whether the Header View supports the given class */
	static bool IsClassHeaderViewSupported(const UClass* InClass);
	
	static void OpenHeaderViewForAsset(FAssetData InAssetData);

	//~ Begin IGBAScaffoldModule interface
	virtual TSharedRef<SWindow> CreateAttributeWizard(const FAssetData& InAssetData, const FGBAAttributeWindowArgs& InArgs) const override;
	//~ End IGBAScaffoldModule interface

	static TSharedRef<SWindow> CreateAttributeWizardWindow(const FAssetData& InAssetData, const FGBAAttributeWindowArgs& InArgs);
	
private: 
	/** Handle to our delegate so we can remove it at module shutdown */
	FDelegateHandle ContentBrowserExtenderDelegateHandle;

	static void SetupAssetEditorMenuExtender();
	void SetupContentBrowserContextMenuExtender();

	static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets);
};
