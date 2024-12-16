// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBAEditorSettings.h"

#include "GBAEditorLog.h"

UGBAEditorSettings::UGBAEditorSettings()
{
	HeaderFormatText = FText::FromString(TEXT("Base: {0}, Current: {1}"));
}

const UGBAEditorSettings& UGBAEditorSettings::Get()
{
	const UGBAEditorSettings* Settings = GetDefault<UGBAEditorSettings>();
	check(Settings);
	return *Settings;
}

UGBAEditorSettings& UGBAEditorSettings::GetMutable()
{
	UGBAEditorSettings* Settings = GetMutableDefault<UGBAEditorSettings>();
	check(Settings);
	return *Settings;
}

FName UGBAEditorSettings::GetCategoryName() const
{
	return PluginCategoryName;
}

FText UGBAEditorSettings::GetSectionText() const
{
	return NSLOCTEXT("GBAEditorSettings", "SectionText", "Details Customizations");
}

void UGBAEditorSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	GBA_EDITOR_LOG(VeryVerbose, TEXT("UGBAEditorSettings::PostEditChangeProperty ... PropertyThatChanged: %s"), *GetNameSafe(PropertyChangedEvent.Property))
}

bool UGBAEditorSettings::IsAttributeFiltered(const TSet<FString>& InFilterList, const FString& InAttributeName)
{
	GBA_EDITOR_LOG(
		VeryVerbose,
		TEXT("UGBAEditorSettings::IsAttributeFiltered - InAttributeName: %s, InFilterList: %s"),
		*InAttributeName,
		*FString::Join(InFilterList, TEXT(", "))
	)

	for (const FString& FilterItem : InFilterList)
	{
		if (InAttributeName.StartsWith(FilterItem))
		{
			GBA_EDITOR_LOG(Verbose, TEXT("\tUGBADeveloperSettings::IsAttributeFiltered - %s filtered by %s"), *InAttributeName, *FilterItem)
			return true;
		}
	}

	return false;
}
