// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "GBAScaffoldPreviewSettings.generated.h"

UENUM()
enum class EGBAPreviewSortMethod : uint8
{
	// Properties will stay in the same order they were in the Blueprint class.
	None,

	// Properties will be grouped together by Access Specifiers, in order of visibility (public, protected, private).
	SortByAccessSpecifier,

	// Properties will be sorted to minimize padding in compiled class layout.
	SortForOptimalPadding
};

USTRUCT(NotBlueprintable)
struct FGBAPreviewSyntaxColors
{
	GENERATED_BODY()

	FGBAPreviewSyntaxColors();

	UPROPERTY(config, EditAnywhere, Category="Settings")
	FLinearColor Comment;

	UPROPERTY(config, EditAnywhere, Category="Settings")
	FLinearColor Error;

	UPROPERTY(config, EditAnywhere, Category="Settings")
	FLinearColor Macro;

	UPROPERTY(config, EditAnywhere, Category="Settings")
	FLinearColor Typename;

	UPROPERTY(config, EditAnywhere, Category="Settings")
	FLinearColor Identifier;

	UPROPERTY(config, EditAnywhere, Category="Settings")
	FLinearColor Keyword;
	
	UPROPERTY(config, EditAnywhere, Category="Settings")
	FLinearColor String;
	
	UPROPERTY(config, EditAnywhere, Category="Settings")
	FLinearColor Numeric;
};

/** Settings for the Blueprint Header View Plugin */
UCLASS(config = EditorPerProjectUserSettings)
class UGBAScaffoldPreviewSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * The category name for our developer settings
	 *
	 * @see GetCategoryName
	 */
	static constexpr const TCHAR* PluginCategoryName = TEXT("Blueprint Attributes");
	
	UGBAScaffoldPreviewSettings();

	//~ Begin UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	virtual FText GetSectionText() const override;
	//~ End UDeveloperSettings interface

protected:
	//~ Begin UObject interface
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject interface

public:
	/** Syntax Highlighting colors for Blueprint Header View output */
	UPROPERTY(config, EditAnywhere, Category="Settings|Style")
	FGBAPreviewSyntaxColors SyntaxColors;

	/** Highlight color for selected items in the Blueprint Header View output */
	UPROPERTY(config, EditAnywhere, Category="Settings|Style")
	FLinearColor SelectionColor = FLinearColor(0.051269f, 0.064803f, 0.099899f, 1.0f);

	/** Font Size for the Blueprint Header View output */
	UPROPERTY(config, EditAnywhere, Category="Settings|Style", meta=(ClampMin=6, ClampMax=72))
	int32 FontSize = 9;

	/** Sorting Method for Header View Functions and Properties */
	UPROPERTY(config, EditAnywhere, Category="Settings")
	EGBAPreviewSortMethod SortMethod = EGBAPreviewSortMethod::None;
};
