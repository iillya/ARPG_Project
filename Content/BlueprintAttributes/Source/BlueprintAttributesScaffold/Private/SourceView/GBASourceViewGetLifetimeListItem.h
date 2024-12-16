// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"

class FGBAAttributeSetWizardViewModel;

/** A header view list item that displays a GetLifetimeReplicatedProps method declaration */
struct FGBASourceViewGetLifetimeListItem : public FGBAHeaderViewListItem
{
	explicit FGBASourceViewGetLifetimeListItem(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);
	
	/** Creates a list item for the Header view representing a declaration for the given blueprint */
	static FGBAHeaderViewListItemPtr Create(const TSharedPtr<FGBAAttributeSetWizardViewModel>& InViewModel);

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface
};
