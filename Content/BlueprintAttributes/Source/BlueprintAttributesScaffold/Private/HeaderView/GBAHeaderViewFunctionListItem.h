// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GBAHeaderViewListItem.h"
#include "Types/SlateEnums.h"

class UK2Node_FunctionEntry;

/** A header view list item that displays a function declaration */
struct FGBAHeaderViewFunctionListItem : public FGBAHeaderViewListItem
{
	/** Creates a list item for the Header view representing a function declaration for the given blueprint function */
	static FGBAHeaderViewListItemPtr Create(const UK2Node_FunctionEntry* FunctionEntry);

	//~ FHeaderViewListItem Interface
	virtual void ExtendContextMenu(FMenuBuilder& InMenuBuilder, TWeakObjectPtr<UObject> InAsset) override;
	virtual void OnMouseButtonDoubleClick(TWeakObjectPtr<UObject> InAsset) override;
	//~ End FHeaderViewListItem Interface

protected:
	/** None if the function name is legal C++, else the name of the function */
	FName IllegalName = NAME_None;

	/** Name of the Function Graph this item represents */
	FName GraphName = NAME_None;

	/** Names of any function parameters that are not legal C++ */
	TArray<FName> IllegalParameters;
	
	explicit FGBAHeaderViewFunctionListItem(const UK2Node_FunctionEntry* FunctionEntry);

	/** Returns a string containing the specifiers for the UFUNCTION line */
	static FString GetConditionalUFunctionSpecifiers(const UFunction* SigFunction);

	/** Adds Function parameters to the RichText and PlainText strings */
	void AppendFunctionParameters(const UFunction* SignatureFunction);

	// UI Callback Functions
	static bool OnVerifyRenameFunctionTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UBlueprint> WeakBlueprint);
	bool OnVerifyRenameParameterTextChanged(const FText& InNewName, FText& OutErrorText, TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName) const;
	static void OnRenameFunctionTextCommitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName);
	void OnRenameParameterTextCommitted(const FText& CommittedText, ETextCommit::Type TextCommitType, TWeakObjectPtr<UBlueprint> WeakBlueprint, FName OldGraphName, FName OldParamName) const;
	void JumpToDefinition(TWeakObjectPtr<UBlueprint> WeakBlueprint) const;
};
