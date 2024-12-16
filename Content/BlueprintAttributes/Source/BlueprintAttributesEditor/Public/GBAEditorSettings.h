// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GBAEditorSettings.generated.h"

/**
 * Common Settings for Blueprint Attributes plugin
 */
UCLASS(config=Game, defaultconfig)
class BLUEPRINTATTRIBUTESEDITOR_API UGBAEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * The category name for our developer settings
	 *
	 * @see GetCategoryName
	 */
	static constexpr const TCHAR* PluginCategoryName = TEXT("Blueprint Attributes");

	UGBAEditorSettings();

	static const UGBAEditorSettings& Get();
	static UGBAEditorSettings& GetMutable();


	//~ Begin UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	virtual FText GetSectionText() const override;
	//~ End UDeveloperSettings interface

	//~ Begin UObject interface
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject interface

	/**
	 * Set of gameplay attributes to ignore in attributes picker widget.
	 *
	 * Allows you to filter out a list of gameplay attributes from Attribute Sets in Gameplay Effects Blueprint
	 * or any Blueprint nodes listing them (such as GetFloatAttribute())
	 *
	 * It can be useful if your project is never using pre-defined Attributes (such as AbilitySystemComponent.OutgoingDuration / IncomingDuration),
	 * or plugins (such as GAS Companion GSCAttributeSet)
	 *
	 * This is a StartsWith search pattern, meaning any value here should be the beginning of an attribute (or set) we'd like to ignore, example:
	 *
	 * - AbilitySystemComponent
	 * - AbilitySystemComponent.OutgoingDuration
	 * - AbilitySystemComponent.IncomingDuration
	 * - GSCAttributeSet
	 * - GSCAttributeSet.Mana
	 */
	UPROPERTY(config, EditAnywhere, Category = "Details Customizations | Attributes", DisplayName = "Filter Out Attributes in Details View")
	TSet<FString> FilterAttributesList;

	/**
	 * Whether to use a compact view mode for Gameplay Attribute Data properties in Attribute Set Blueprints.
	 *
	 * For both class defaults variables and when viewing / editing a single Attribute Data property, making the edition of
	 * BaseValue possible in the header of the row.
	 *
	 * Only for simple Gameplay Attribute Data properties, clamped properties still display using the full extended version.
	 */
	UPROPERTY(config, EditAnywhere, Category = "Details Customizations | Attribute Data Properties")
	bool bUseCompactView = false;

	/**
	 * Customize how the header row is displayed and what should be included.
	 *
	 * This is a FText::Format format string, with two floats being passed in as an argument (BaseValue and CurrentValue). Both float
	 * values are converted to String with "%.2f" to reduce precision to only two decimals.
	 *
	 * Default Value: "Base: {0}, Current: {1}"
	 */
	UPROPERTY(config, EditAnywhere,  Category = "Details Customizations | Attribute Data Properties", meta = (EditCondition="!bUseCompactView", EditConditionHides))
	FText HeaderFormatText;
	
	/**
	 * Whether to display Attributes' CurrentValue property as well, as a BlueprintReadOnly property (not editable).
	 *
	 * CurrentValue is kept in sync with BaseValue when edited within the details panel.
	 */
	UPROPERTY(config, EditAnywhere, Category = "Details Customizations | Attribute Data Properties", meta = (EditCondition="!bUseCompactView", EditConditionHides))
	bool bDisplayCurrentValue = false;

	/** Helper to check if a given attribute property is filtered by FilterAttributesList */
	static bool IsAttributeFiltered(const TSet<FString>& InFilterList, const FString& InAttributeName);
};
