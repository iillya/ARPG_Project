// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakFieldPtr.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SWidget.h"
#include "Widgets/Input/SComboButton.h"

class SGBAGameplayAttributeWidget : public SCompoundWidget
{
public:

	/** Called when a tag status is changed */
	DECLARE_DELEGATE_OneParam(FOnAttributeChanged, FProperty*)

	SLATE_BEGIN_ARGS(SGBAGameplayAttributeWidget)
	: _DefaultProperty(nullptr)
	, _FilterClass(nullptr)
	{}
	SLATE_ARGUMENT(FString, FilterMetaData)
	SLATE_ARGUMENT(FProperty*, DefaultProperty)
	SLATE_ARGUMENT(const UClass*, FilterClass)
	SLATE_ARGUMENT(bool, ShowOnlyOwnedAttributes)
	SLATE_EVENT(FOnAttributeChanged, OnAttributeChanged) // Called when a tag status changes
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FProperty* GetSelectedProperty() const { return SelectedPropertyPtr.Get(); }
	void SetSelectedProperty(const FProperty* InSelectedProperty) { SelectedPropertyPtr = InSelectedProperty; }

private:

	TSharedRef<SWidget> GenerateAttributePicker();

	FText GetSelectedValueAsString() const;

	/** Handles updates when the selected attribute changes */
	void OnAttributePicked(FProperty* InProperty);

	/** Delegate to call when the selected attribute changes */
	FOnAttributeChanged OnAttributeChanged;

	/** The search string being used to filter the attributes */
	FString FilterMetaData;

	/** The currently selected attribute */
	TWeakFieldPtr<FProperty> SelectedPropertyPtr;

	/** Used to display an attribute picker. */
	TSharedPtr<SComboButton> ComboButton;
	
	/** Attribute set Class we want to see attributes of */
	TWeakObjectPtr<const UClass> FilterClass;
	
	/** Whether to filter the attribute list to only attributes owned by the containing class */
	bool bShowOnlyOwnedAttributes = false;
};
