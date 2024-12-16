// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"
#include "Types/SlateEnums.h"

class FGBAAttributeSetWizardViewModel;
class FMenuBuilder;

/** A header view list item that displays the class declaration */
struct FGBAHeaderViewClassListItem : public FGBAHeaderViewListItem
{
	explicit FGBAHeaderViewClassListItem(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	/** Creates a list item for the Header view representing a class declaration for the given blueprint */
	static FGBAHeaderViewListItemPtr Create(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface

protected:
	/** Whether this class name is valid C++ (no spaces, special chars, etc) */
	bool bIsValidName = true;

	static FString GetConditionalUClassSpecifiers(const UBlueprint* Blueprint);

	FString GetRenamedBlueprintPath(const UBlueprint* Blueprint, const FString& NewName) const;

	bool OnVerifyRenameTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UBlueprint> InBlueprint) const;

	void OnRenameTextCommitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UBlueprint> InBlueprint) const;
};
