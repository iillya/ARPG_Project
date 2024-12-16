// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "UObject/WeakFieldPtr.h"

class FGBABlueprintEditor;
class UAttributeSet;
struct FGameplayAttributeData;

/**
 * Details customization for FGameplayAttributeData / FGBAGameplayClampedAttributeData (Base Class).
 *
 * And ability to view / set BaseValue and CurrentValue (as DefaultValue)
 *
 * This is the default Base class shared by both FGameplayAttributeData and FGBAGameplayClampedAttributeData details customization classes.
 */
class IGBAGameplayAttributeDataDetailsBase : public IPropertyTypeCustomization
{
public:
	IGBAGameplayAttributeDataDetailsBase();
	virtual ~IGBAGameplayAttributeDataDetailsBase() override;

	/** Setup - mainly to register SP delegates as they need to happen after construction */
	virtual void Initialize();
	virtual void InitializeFromStructHandle(const TSharedRef<IPropertyHandle>& InStructPropertyHandle, IPropertyTypeCustomizationUtils& InStructCustomizationUtils);
	virtual FGameplayAttributeData* GetGameplayAttributeData() const;

	//~ Begin IPropertyTypeCustomization interface
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override {}
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override {}
	//~ End IPropertyTypeCustomization interface

protected:
	/** Keep track of the property we are editing */
	TWeakFieldPtr<FProperty> PropertyBeingCustomized;

	/** The UObject we are editing */
	TWeakObjectPtr<UAttributeSet> AttributeSetBeingCustomized;
	
	/**
	 * Keep track of the FGameplayAttributeData struct we are editing
	 *
	 * This is mostly for GetGameplayAttributeData() implementation and GetHeaderBaseValueText() handling (reading
	 * Base and CurrentValue to display in headings)
	 */
	TSharedPtr<FGameplayAttributeData*> AttributeDataBeingCustomized;

	/** A weak reference to the property utilities used by this type customization */
	TWeakPtr<IPropertyUtilities> PropertyUtilities;

	void HandleSettingsChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);

	static bool IsCompactView();

	FText GetHeaderBaseValueText() const;
};
