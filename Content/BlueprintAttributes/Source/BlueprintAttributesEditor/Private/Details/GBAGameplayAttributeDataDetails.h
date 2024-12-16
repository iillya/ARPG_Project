// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGBAGameplayAttributeDataDetailsBase.h"

class IPropertyHandle;
class IPropertyTypeCustomization;

/**
 * Details customization for FGameplayAttributeData.
 *
 * And ability to view / set BaseValue and CurrentValue (as DefaultValue)
 */
class FGBAGameplayAttributeDataDetails : public IGBAGameplayAttributeDataDetailsBase
{
public:
	FGBAGameplayAttributeDataDetails();
	virtual ~FGBAGameplayAttributeDataDetails() override;

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	//~ Begin IPropertyTypeCustomization interface
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;
	//~ End IPropertyTypeCustomization interface

	void CustomizeBaseValueChildren(const TSharedRef<IPropertyHandle>& InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils, const bool bAllowCompactView) const;
	static void CustomizeCurrentValueChildren(const TSharedRef<IPropertyHandle>& InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils);
};
