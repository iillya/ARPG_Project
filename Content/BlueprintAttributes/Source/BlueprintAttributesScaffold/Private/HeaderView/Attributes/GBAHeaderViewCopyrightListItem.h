// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"

class FGBAAttributeSetWizardViewModel;

/** A header view list item that displays a GetLifetimeReplicatedProps method declaration */
struct FGBAHeaderViewCopyrightListItem : public FGBAHeaderViewListItem
{
	FGBAHeaderViewCopyrightListItem();
	
	/** Creates a list item for the Header view representing a declaration for the given blueprint */
	static FGBAHeaderViewListItemPtr Create();

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface

protected:

	/** None if the name is legal, else holds the name of the variable */
	FName IllegalName = NAME_None;
};
