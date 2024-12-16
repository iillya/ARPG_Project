// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Kismet/Public/BlueprintEditor.h"

class FGBANewAttributeViewModel;

/**
 * Blueprint Attribute Set asset editor (extends Blueprint editor)
 */
class FGBABlueprintEditor : public FBlueprintEditor
{
public:
	FGBABlueprintEditor();
	virtual ~FGBABlueprintEditor() override;

	/**
	 * Edits the specified gameplay ability asset(s)
	 *
	 * @param	Mode					Asset editing mode for this editor (standalone or world-centric)
	 * @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within
	 * @param	InBlueprints			The blueprints to edit
	 * @param	bShouldOpenInDefaultsMode	If true, the editor will open in defaults editing mode
	 */
	void InitAttributeSetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode);

	//~ Begin FBlueprintEditor interface
	virtual void Compile() override;
	virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;
	//~ End FBlueprintEditor interface

	// IToolkit interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	// End of IToolkit interface

	/** @return the documentation location for this editor */
	virtual FString GetDocumentationLink() const override;

	TWeakObjectPtr<UObject> GetLastPinSubCategoryObject() const;
	void SetLastPinSubCategoryObject(const TWeakObjectPtr<UObject>& InLastPinSubCategoryObject);
	bool GetLastReplicatedState() const;
	void SetLastReplicatedState(const bool bInLastReplicatedState);
	FString GetLastUsedVariableName() const;
	void SetLastUsedVariableName(const FString& InLastUsedVariableName);

private:
	/** Holds a reference to attribute wizard window to only allow one instance at a time */
	TSharedPtr<SWindow> AttributeWizardWindow;

	/** Holds a reference to attribute wizard window to only allow one instance at a time */
	TSharedPtr<SWindow> DataTableWindow;

	/**
	 * The last pin type used (to add a new Attribute variable), storing the struct used as a
	 * UObject (equivalent of PinType PinSubCategoryObject)
	 */
	TWeakObjectPtr<UObject> LastPinSubCategoryObject;

	/** The last replicated state used (to add a new Attribute variable via toolbar or details button) */
	bool bLastReplicatedState = true;

	/** The last used variable name (to add a new Attribute variable via toolbar or details button) */
	FString LastUsedVariableName;

	/** Construct toolbar widgets for custom actions */
	void FillToolbar(FToolBarBuilder& InToolbarBuilder);

	/** Creates widget for toolbar content */
	TSharedRef<SWidget> GenerateToolbarMenu();

	static void HandleAttributeWindowCancel(const TSharedPtr<FGBANewAttributeViewModel>& InViewModel);
	void HandleAttributeWindowFinish(const TSharedPtr<FGBANewAttributeViewModel>& InViewModel);

	void CreateAttributeWizard();
	void HandleAttributeWizardClosed(const TSharedRef<SWindow>& InWindow);

	void CreateDataTableWindow();
	void HandleDataTableWindowClosed(const TSharedRef<SWindow>& InWindow);
};
