// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"
#include "Types/SlateEnums.h"

class FGBAAttributeSetWizardViewModel;
struct FBPVariableDescription;

/** A header view list item that displays a variable declaration */
struct FGBAHeaderViewVariableListItem : public FGBAHeaderViewListItem
{
	FGBAHeaderViewVariableListItem(const FProperty& InVarProperty, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	/** Creates a list item for the Header view representing a variable declaration for the given blueprint variable */
	static FGBAHeaderViewListItemPtr Create(const FProperty& VarProperty, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface


	static FBPVariableDescription* GetBlueprintVariableDescription(const FName& InVarPropertyName, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

protected:
	/** None if the name is legal, else holds the name of the variable */
	FName IllegalName = NAME_None;

	// FBPVariableDescription* Get

	/** Formats a line declaring a delegate type and appends it to the item strings */
	void FormatDelegateDeclaration(const FMulticastDelegateProperty& DelegateProp);

	/** Returns a string containing the specifiers for the UPROPERTY line */
	FString GetConditionalUPropertySpecifiers(const FProperty& VarProperty) const;

	/** Returns the name of the owning class */
	static FString GetOwningClassName(const FProperty& VarProperty);

	bool OnVerifyRenameTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UObject> WeakAsset) const;
	void OnRenameTextCommitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UObject> WeakAsset) const;
};
