// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FSlateBrush;
struct FSlateFontInfo;

/**
 * AppStyle class specific to this module
 *
 * Wraps access to either FAppStyle or FEditorStyle based on engine version.
 */
class BLUEPRINTATTRIBUTESEDITORCOMMON_API FGBAAppStyle
{
public:
	static const FSlateBrush* GetBrush(const FName& InPropertyName, const ANSICHAR* InSpecifier = nullptr);
	static FSlateFontInfo GetFontStyle(const FName& InPropertyName, const ANSICHAR* InSpecifier = nullptr);
};
