// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

class SGBAGameplayAttributeWidget;

/**
 * This is the main customization class for FGameplayAttribute properties
 *
 * Its almost identical to the engine customization for FGameplayAttribute, its main purpose is to make use of
 * SGBAGameplayAttributeWidget to allow the display of FGameplayAttribute FProperties in Attribute picker dropdown.
 */
class FGBAGameplayAttributePropertyDetails : public IPropertyTypeCustomization
{
public:
	virtual ~FGBAGameplayAttributePropertyDetails() override;

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:

	/** The attribute property */
	TSharedPtr<IPropertyHandle> MyProperty;

	/** The owner property */
	TSharedPtr<IPropertyHandle> OwnerProperty;

	/** The name property */
	TSharedPtr<IPropertyHandle> NameProperty;

	/** Slate Attribute Widget */
	TSharedPtr<SGBAGameplayAttributeWidget> AttributeWidget;

	void OnAttributeChanged(FProperty* SelectedAttribute) const;
	
	void HandleRequestRefresh(const TSharedPtr<IPropertyUtilities> InPropertyUtilities);
};
