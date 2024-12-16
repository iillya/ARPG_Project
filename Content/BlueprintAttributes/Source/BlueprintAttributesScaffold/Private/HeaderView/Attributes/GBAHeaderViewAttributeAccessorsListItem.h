// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"

/** A header view list item that displays a list of include directives */
struct FGBAHeaderViewAttributesAccessorsListItem : public FGBAHeaderViewListItem
{
	FGBAHeaderViewAttributesAccessorsListItem();

	/** Creates a list item for the Header view representing a declaration for the given blueprint */
	static FGBAHeaderViewListItemPtr Create();

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface
};
