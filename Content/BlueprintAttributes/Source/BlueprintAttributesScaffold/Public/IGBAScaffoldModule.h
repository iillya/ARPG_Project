// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Widgets/SWindow.h"

struct FGBAAttributeWindowArgs
{
	FText Title = NSLOCTEXT("IGBAScaffoldModule", "DefaultWindowTitle", "Create new C++ Attribute Set");
	FVector2d Size = FVector2D(1280, 720);
	ESizingRule SizingRule = ESizingRule::UserSized;
	bool bSupportsMinimize = true;
	bool bSupportsMaximize = true;
	bool bIsModal = false;

	FGBAAttributeWindowArgs() = default;
};

/** Module interface for scaffold module */
class IGBAScaffoldModule : public IModuleInterface
{
public:
	/**
	 * Singleton-like access to this module's interface. This is just for convenience!
	 * Beware of calling this during the shutdown phase, though. Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static IGBAScaffoldModule& Get()
	{
		static const FName ModuleName = "BlueprintAttributesScaffold";
		return FModuleManager::LoadModuleChecked<IGBAScaffoldModule>(ModuleName);
	}

	/**
	 * Checks to see if this module is loaded and ready. It is only valid to call Get() during shutdown if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static bool IsAvailable()
	{
		static const FName ModuleName = "BlueprintAttributesScaffold";
		return FModuleManager::Get().IsModuleLoaded(ModuleName);
	}

	/** Creates and returns a new wizard widget to create attribute C++ class from a Blueprint AttributeSet. */
	virtual TSharedRef<SWindow> CreateAttributeWizard(const FAssetData& InAssetData, const FGBAAttributeWindowArgs& InArgs) const = 0;
};
