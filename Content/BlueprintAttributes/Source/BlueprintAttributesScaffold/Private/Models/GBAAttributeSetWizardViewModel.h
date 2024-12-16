// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameProjectUtils.h"
#include "ViewModel/IGBASlateViewModel.h"

/** Where is this class located within the Source folder? */
enum class EGBAPreviewCppType : uint8
{
	/** Previewing header file */
	Header,

	/** Previewing source file */
	Source,
};

struct FGBARequiredModuleDependency
{
	FString ModuleName;
	FText Reason;

	FGBARequiredModuleDependency() = default;

	FGBARequiredModuleDependency(const FString& InModuleName, const FText& InReason)
		: ModuleName(InModuleName)
		, Reason(InReason)
	{
	}

	bool operator<(const FGBARequiredModuleDependency& InOther) const
	{
		return ModuleName < InOther.ModuleName;
	}

	bool operator==(const FString& InOther) const
	{
		return ModuleName == InOther;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("%s (%s)"), *ModuleName, *Reason.ToString());
	}
};

/**
 * Implements a view model for the attribute set wizard.
 */
class FGBAAttributeSetWizardViewModel : public IGBASlateViewModel
{
public:
	/** Whether the class should be created as a Public or Private class */
	DECLARE_VIEWMODEL_PROPERTY(GameProjectUtils::EClassLocation, ClassLocation);

	/** The name of the class being created (Value of Name Edit box) */
	DECLARE_VIEWMODEL_PROPERTY(FString, NewClassName);

	/** The selected parent class */
	DECLARE_VIEWMODEL_PROPERTY(FNewClassInfo, ParentClassInfo);

	/** Information about the currently selected module; used for class validation */
	DECLARE_VIEWMODEL_PROPERTY(TSharedPtr<FModuleContextInfo>, SelectedModuleInfo);

	/** The displayed and edited path to place the file for the class being generated, relative to target module source path */
	DECLARE_VIEWMODEL_PROPERTY(FString, SelectedClassPath);

	/** The asset currently being displayed by the header view */
	DECLARE_VIEWMODEL_PROPERTY(TWeakObjectPtr<UBlueprint>, SelectedBlueprint);

	/** Current value for the segmented control active view */
	DECLARE_VIEWMODEL_PROPERTY(EGBAPreviewCppType, CurrentPreviewValue);

	/** The path to place the files for the class being generated */
	DECLARE_VIEWMODEL_PROPERTY(FString, NewClassPath);

	/** The calculated name of the generated header file for this class */
	DECLARE_VIEWMODEL_PROPERTY(FString, CalculatedClassHeaderName);

	/** The calculated name of the generated source file for this class */
	DECLARE_VIEWMODEL_PROPERTY(FString, CalculatedClassSourceName);
	
	/** List of required module dependencies for class being generated (dynamic based on parent class and other parameters) */
	DECLARE_VIEWMODEL_PROPERTY(TArray<FGBARequiredModuleDependency>, RequiredModuleDependencies);
	
	/** List of missing module dependencies for class being generated (updated as part of the validation process) */
	DECLARE_VIEWMODEL_PROPERTY(TArray<FString>, MissingModuleDependencies);
	
	/** Whether all required module dependencies are present in target module Build.cs file */
	DECLARE_VIEWMODEL_PROPERTY(bool, bSatisfiesModuleDependencies);

	/** Delegate called whenever input and model properties are validated passing down whether it was valid, and an error text if not */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateValidityChanged, bool, const FText&);

	FOnUpdateValidityChanged& OnUpdateValidityChanged() { return OnUpdateValidityChangedDelegate; }

	/** Default constructor with ParentClass set to UAttributeSet */
	FGBAAttributeSetWizardViewModel();

	/** Convenience constructor so you can construct from a FNewClassInfo */
	explicit FGBAAttributeSetWizardViewModel(const FNewClassInfo& InParentClassInfo);

	/** Convenience constructor so you can construct from a UClass */
	explicit FGBAAttributeSetWizardViewModel(const UClass* InClass);

	/** Noop (for now) initialization sequence */
	virtual void Initialize() override;

	/** Checks the current class name/path for validity and updates cached values accordingly */
	void UpdateInputValidity();

	/** Returns whether last validity check was successful */
	bool IsLastInputValidityCheckSuccessful() const;

	/** Returns localized text with error info in case last input validity check failed */
	FText GetLastInputValidityErrorText() const;

	/**
	 * Runs periodic check to check the class name/path for validity in case the disk contents changed and the location is now valid or invalid.
	 *
	 * After class creation, periodic checks are disabled to prevent a brief message indicating that the class you created already exists.
	 *
	 * This feature is re-enabled if the user did not restart and began editing parameters again.
	 */
	void RunPeriodicValidationOnTick(const double InCurrentTime);

	/** Adds a new required module dependency if it's not the currently selected module */
	void AddRequiredModuleDependency(const FString& InModuleName, const FText& InReason);

	/** Reset required module dependencies to the reserved always included ones */
	void ResetRequiredModuleDependencies();

private:
	/** The list of "reserved" always required dependencies */
	static TArray<FGBARequiredModuleDependency> ReservedModuleDependencies;
	
	/** Delegate invoked at the end of a new validity check */
	FOnUpdateValidityChanged OnUpdateValidityChangedDelegate;

	/** The error text from the last validity check */
	FText LastInputValidityErrorText;

	/** True if the last validity check returned that the class name/path is valid for creation */
	bool bLastInputValidityCheckSuccessful = false;

	/** The last time that the class name/path was checked for validity. This is used to throttle I/O requests to a reasonable frequency */
	double LastPeriodicValidityCheckTime = 0;

	/** The frequency in seconds for validity checks while the dialog is idle. Changes to the name/path immediately update the validity. */
	double PeriodicValidityCheckFrequency = 4;

	/** Periodic checks for validity will not occur while this flag is true. Used to prevent a frame of "this project already exists" while exiting after a successful creation. */
	bool bPreventPeriodicValidityChecksUntilNextChange = false;
};
