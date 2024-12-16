// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameProjectUtils.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SComboBox.h"

class FGBAAttributeSetWizardViewModel;
class SComboButton;
class SEditableTextBox;

/**
 * Slate widget representing the top part Attribute Set cpp creation window.
 *
 * Holds info such as ClassName, ClassPath, BaseClass, etc.
 */
class SGBAClassInfo : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGBAClassInfo) {}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

protected:
	/** Keep a reference to the last selected module, so we can init it when re-opening the wizard */
	static FString LastSelectedModuleName;
	
	/** View model for our widget (passed down from container widget) */
	TSharedPtr<FGBAAttributeSetWizardViewModel> ViewModel;
	
	/** Information about the currently available modules for this project */
	TArray<TSharedPtr<FModuleContextInfo>> AvailableModules;

	/** The editable text box to enter the current name */
	TSharedPtr<SEditableTextBox> ClassNameEditBox;

	/** The available modules combo box */
	TSharedPtr<SComboBox<TSharedPtr<FModuleContextInfo>>> AvailableModulesCombo;
	
	/** Reference to the Class Picker combo button widget */
	TSharedPtr<SComboButton> ParentClassPickerComboButton;
	
	/** Init list of AvailableModules, based on project / plugin modules currently loaded */
	void InitAvailableModules();
	
	/** Returns best suited module for target module */
	TSharedPtr<FModuleContextInfo> InitSelectedModuleInfo();

	/** Checks to see if the given class location is active based on the current value of NewClassPath */
	GameProjectUtils::EClassLocation GetClassLocation() const;

	/** Update the value of NewClassPath so that it uses the given class location */
	void OnClassLocationChanged(GameProjectUtils::EClassLocation InLocation) const;

	/** Returns the text in the class name edit box */
	FText OnGetClassNameText() const;

	/** Handler for when the text in the class name edit box has changed */
	void OnClassNameTextChanged(const FText& InNewText) const;

	/** Get the combo box text for the currently selected module */
	FText GetSelectedModuleComboText() const;

	/** Called when the currently selected module is changed */
	void HandleSelectedModuleComboBoxSelectionChanged(TSharedPtr<FModuleContextInfo> InSelectedModuleInfo, ESelectInfo::Type InSelectInfo) const;

	/** Create the widget to use as the combo box entry for the given module info */
	TSharedRef<SWidget> MakeWidgetForSelectedModuleCombo(TSharedPtr<FModuleContextInfo> InValue) const;

	/** Returns the text in the class path edit box */
	FText OnGetClassPathText() const;

	/** Enables / disables input depending on valid user folder selection */
	bool IsClassPathTextEnabled() const;

	/** Handler for when the text in the class path edit box has changed */
	void OnClassPathTextChanged(const FText& InNewText);

	/** Compute new fully qualified class path */
	FString CalculateNewClassPath(GameProjectUtils::EClassLocation InLocation, const FString& InNewClassPath) const;

	/** Returns the text for the calculated header file name */
	FText OnGetClassHeaderFileText() const;

	/** Returns the text for the calculated source file name */
	FText OnGetClassSourceFileText() const;

	/** Handler for when the "Choose Folder" button is clicked */
	FReply HandleChooseFolderButtonClicked();
	
	/** Gets the text for the class picker combo button */
	FText GetClassPickerText(const bool bIsTooltipText = false) const;

	/** Constructs a Blueprint Class picker menu widget */
	TSharedRef<SWidget> GetClassPickerMenuContent();
	
	/** Handler for the class viewer selection on parent class */
	void OnParentClassSelected(UClass* InParentClass) const;
};
