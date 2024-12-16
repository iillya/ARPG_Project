// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FGBANewAttributeViewModel;
class INameValidatorInterface;
class SEditableTextBox;
class UBlueprint;
enum class ECheckBoxState : uint8;
struct FEdGraphPinType;

/**
 * Slate widget to handle addition of a new Blueprint Attribute variable in Attribute Sets (used from Details customization)
 *
 * Provides a form to specify variable name, description, replication condition, and so on...
 */
class SGBANewAttributeVariableWidget : public SCompoundWidget
{
public:

	DECLARE_DELEGATE_OneParam(FOnWindowClosed, const TSharedPtr<FGBANewAttributeViewModel>&);
	
	SLATE_BEGIN_ARGS(SGBANewAttributeVariableWidget) {}

	SLATE_EVENT(FOnWindowClosed, OnCancel)
	SLATE_EVENT(FOnWindowClosed, OnFinish)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TSharedPtr<FGBANewAttributeViewModel>& InViewModel);

	static bool AddMemberVariable(UBlueprint* InBlueprint, const FString& InVarName, const FEdGraphPinType& InPinType, const FString& InDescription, const bool bInIsReplicated);
	static void ReplicationOnRepFuncChanged(UBlueprint* InBlueprint, const FString& InNewOnRepFunc, const FName& InVarName);

private:
	/** Desired Size overrides, to ensure it has a minimum width / height */
	static FVector2d DesiredSizeOverride;
	
	/** View model for this widget */
	TSharedPtr<FGBANewAttributeViewModel> ViewModel;

	/** The widget used when in variable name editing mode */
	TSharedPtr<SEditableTextBox> VarNameEditableTextBox;

	/** Name validator for BP variable names */
	TSharedPtr<INameValidatorInterface> NameValidator;
	
	/** Invoked when user clicks the Cancel button */
	FOnWindowClosed OnCancelDelegate;
	
	/** Invoked when user clicks the Cancel button */
	FOnWindowClosed OnFinishDelegate;

	/** Creates an appropriate name validator */
	TSharedPtr<INameValidatorInterface> CreateNameValidator() const;

	FText OnGetVarName() const;
	void OnVarNameChanged(const FText& InText) const;
	void OnVarNameCommitted(const FText& InText, ETextCommit::Type InTextCommit);
	bool HandleVerifyVariableNameChanged(const FText& InText, FText& OutErrorText) const;
	
	FEdGraphPinType OnGetVarType() const;
	void OnVarTypeChanged(const FEdGraphPinType& InEdGraphPin) const;

	FText HandleGetDescriptionText() const;
	void HandleDescriptionTextCommitted(const FText& InText, ETextCommit::Type InArg) const;
	void HandleDescriptionTextChanged(const FText& InText) const;
	
	ECheckBoxState HandleGetReplicationCheckboxState() const;
	void HandleReplicationCheckboxStateChanged(ECheckBoxState InCheckBoxState) const;

	virtual FVector2D ComputeDesiredSize(float InLayoutScaleMultiplier) const override;
	
	FReply HandleCancelButtonClicked();
	FReply HandleFinishButtonClicked();
	bool CanFinish() const;
	
	void CloseWindow();

	/**
	 * Wrapper on top of FBlueprintEditorUtils::FindUniqueKismetName
	 *
	 * Abstracts away subtle difference between 5.0 and 5.1. Internal implementation changed to only suffix with _{Number} if
	 * original name is not valid (eg. existing variable name) while on 5.0 input name is always considered invalid.
	 */
	static FName FindUniqueKismetName(const UBlueprint* InBlueprint, const FString& InBaseName, UStruct* InScope = nullptr);
};
