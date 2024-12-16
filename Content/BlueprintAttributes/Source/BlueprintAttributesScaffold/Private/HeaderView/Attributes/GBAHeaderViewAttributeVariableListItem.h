// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"
#include "Types/SlateEnums.h"

struct FGameplayAttributeData;
class FGBAAttributeSetWizardViewModel;
struct FBPVariableDescription;

/** A header view list item that displays a gameplay attribute data variable declaration */
struct FGBAHeaderViewAttributeVariableListItem : public FGBAHeaderViewListItem
{
	FGBAHeaderViewAttributeVariableListItem(const FProperty& InVarProperty, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	/** Creates a list item for the Header view representing a variable declaration for the given blueprint variable */
	static FGBAHeaderViewListItemPtr Create(const FProperty& InVarProperty, const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface

protected:
	/** Returns a string containing the specifiers for the UPROPERTY line */
	static FString GetConditionalUPropertySpecifiers(const FProperty& VarProperty);

	bool OnVerifyRenameTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UObject> WeakAsset) const;
	void OnRenameTextCommitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UObject> WeakAsset) const;

	/** None if the name is legal, else holds the name of the variable */
	FName IllegalName = NAME_None;
	
	TSharedPtr<FGameplayAttributeData> GetGameplayAttributeData(const FProperty& InProperty) const;
};
