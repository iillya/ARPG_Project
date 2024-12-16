// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"

/** A header view list item that displays a gameplay attribute data variable declaration */
struct FGBAHeaderViewOnRepListItem : public FGBAHeaderViewListItem
{
	/** Creates a list item for the Header view representing a variable declaration for the given blueprint variable */
	static FGBAHeaderViewListItemPtr Create(const FProperty& VarProperty);

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface

protected:
	explicit FGBAHeaderViewOnRepListItem(const FProperty& VarProperty);

	/** None if the name is legal, else holds the name of the variable */
	FName IllegalName = NAME_None;
};
