// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AddToProjectConfig.h"
#include "AssetRegistry/AssetData.h"
#include "Widgets/SCompoundWidget.h"

class FGBAAttributeSetWizardViewModel;
class SGBAClassInfo;
class SGBAHeaderView;
class SWizard;
struct FModuleContextInfo;

/**
 * Main slate widget wrapping a wizard with:
 *
 * Wizard
 * -> SGBAClassInfo
 * -> SGBAHeaderView
 */
class SGBAAttributeSetWizard : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGBAAttributeSetWizard) {}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const FAssetData& InAssetData);
	virtual ~SGBAAttributeSetWizard() override;
	
	/**
	 * Runs periodic check to check the class name/path for validity in case the disk contents changed and the location is now valid or invalid.
	 *
	 * After class creation, periodic checks are disabled to prevent a brief message indicating that the class you created already exists.
	 *
	 * This feature is re-enabled if the user did not restart and began editing parameters again.
	 */
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

protected:
	/** Main wizard */
	TSharedPtr<SWizard> Wizard;

	/** Main model */
	TSharedPtr<FGBAAttributeSetWizardViewModel> ViewModel;

	/** Header View widget */
	TSharedPtr<SGBAHeaderView> HeaderViewWidget;

	/** Cached argument asset data to pass down to header view */
	FAssetData AssetData;

	/** Handler for when cancel is clicked */
	void CancelClicked();

	/** Returns true if Finish is allowed */
	bool CanFinish() const;

	/** Handler for when finish is clicked */
	void FinishClicked();

	/** Closes the window that contains this widget */
	void CloseContainingWindow();

	/** Returns blueprint of passed in asset data, if it's a valid UBlueprint */
	static FString GetBlueprintName(const FAssetData& InAssetData);

	/** Gets the visibility of the global error label */
	EVisibility GetGlobalErrorLabelVisibility() const;

	/** Gets the text to display in the global error label */
	FText GetGlobalErrorLabelText() const;

	/**	Handler for when class parent is changed in model. Used to update the list of require module dependencies */
	void HandleClassInfoChanged(const FNewClassInfo& InOldClassInfo, const FNewClassInfo& InNewClassInfo) const;
	
	/**	Handler for when selected module is changed in model. Used to update the list of require module dependencies */
	void HandleSelectedModuleInfoChanged(const TSharedPtr<FModuleContextInfo>& InOldModuleContextInfo, const TSharedPtr<FModuleContextInfo>& InNewModuleContextInfo) const;
	
	/**	Handler for when selected blueprint is changed in model. Used to update the list of require module dependencies */
	void HandleSelectedBlueprintChanged(const TWeakObjectPtr<UBlueprint>& InOldBlueprint, const TWeakObjectPtr<UBlueprint>& InNewBlueprint) const;

	void UpdateRequiredModuleDependenciesIfNeeded() const;
};
