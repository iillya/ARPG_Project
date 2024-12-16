// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "IGBAGameplayAttributeDataDetailsBase.h"

#include "AttributeSet.h"
#include "GBAEditorLog.h"
#include "GBAEditorSettings.h"
#include "IPropertyUtilities.h"
#include "PropertyHandle.h"

#define LOCTEXT_NAMESPACE "GBAGameplayAttributeDataDetails"

IGBAGameplayAttributeDataDetailsBase::IGBAGameplayAttributeDataDetailsBase()
{
	GBA_EDITOR_LOG(VeryVerbose, TEXT("Construct IGBAGameplayAttributeDataDetailsBase ..."))
}

IGBAGameplayAttributeDataDetailsBase::~IGBAGameplayAttributeDataDetailsBase()
{
	GBA_EDITOR_LOG(VeryVerbose, TEXT("Destroyed IGBAGameplayAttributeDataDetailsBase ..."))
	PropertyBeingCustomized.Reset();
	AttributeSetBeingCustomized.Reset();
	AttributeDataBeingCustomized.Reset();

	UGBAEditorSettings::GetMutable().OnSettingChanged().RemoveAll(this);
}

void IGBAGameplayAttributeDataDetailsBase::Initialize()
{
	UGBAEditorSettings::GetMutable().OnSettingChanged().AddSP(this, &IGBAGameplayAttributeDataDetailsBase::HandleSettingsChanged);
}

void IGBAGameplayAttributeDataDetailsBase::InitializeFromStructHandle(const TSharedRef<IPropertyHandle>& InStructPropertyHandle, IPropertyTypeCustomizationUtils& InStructCustomizationUtils)
{
	PropertyUtilities = InStructCustomizationUtils.GetPropertyUtilities();

	PropertyBeingCustomized = InStructPropertyHandle->GetProperty();
	check(PropertyBeingCustomized.IsValid());

	const UClass* OwnerClass = PropertyBeingCustomized->Owner.GetOwnerClass();
	check(OwnerClass);
	
	const UClass* OuterBaseClass = InStructPropertyHandle->GetOuterBaseClass();
	check(OuterBaseClass);

	AttributeSetBeingCustomized = Cast<UAttributeSet>(OuterBaseClass->GetDefaultObject());
	
	if (FGameplayAttribute::IsGameplayAttributeDataProperty(PropertyBeingCustomized.Get()))
	{
		const FStructProperty* StructProperty = CastField<FStructProperty>(PropertyBeingCustomized.Get());
		check(StructProperty);

		if (FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(AttributeSetBeingCustomized.Get()))
		{
			AttributeDataBeingCustomized = MakeShared<FGameplayAttributeData*>(DataPtr);
		}
	}
}

FGameplayAttributeData* IGBAGameplayAttributeDataDetailsBase::GetGameplayAttributeData() const
{
	if (!AttributeDataBeingCustomized.IsValid())
	{
		return nullptr;
	}

	return *AttributeDataBeingCustomized.Get();
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable CppParameterMayBeConstPtrOrRef
void IGBAGameplayAttributeDataDetailsBase::HandleSettingsChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent)
{
	GBA_EDITOR_LOG(VeryVerbose, TEXT("IGBAGameplayAttributeDataDetailsBase::HandleSettingsChanged - InObject: %s, Property: %s"), *GetNameSafe(InObject), *GetNameSafe(InPropertyChangedEvent.Property))

	if (const TSharedPtr<IPropertyUtilities> Utilities = PropertyUtilities.Pin())
	{
		GBA_EDITOR_LOG(VeryVerbose, TEXT("IGBAGameplayAttributeDataDetailsBase::HandleSettingsChanged - ForceRefresh InObject: %s, Property: %s"), *GetNameSafe(InObject), *GetNameSafe(InPropertyChangedEvent.Property))
		Utilities->ForceRefresh();
	}
}

bool IGBAGameplayAttributeDataDetailsBase::IsCompactView()
{
	return UGBAEditorSettings::Get().bUseCompactView;
}

FText IGBAGameplayAttributeDataDetailsBase::GetHeaderBaseValueText() const
{
	const FGameplayAttributeData* AttributeData = GetGameplayAttributeData();
	check(AttributeData);
	
	return FText::Format(
		UGBAEditorSettings::Get().HeaderFormatText,
		FText::FromString(FString::Printf(TEXT("%.2f"), AttributeData->GetBaseValue())),
		FText::FromString(FString::Printf(TEXT("%.2f"), AttributeData->GetCurrentValue()))
	);
}

#undef LOCTEXT_NAMESPACE
