// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Styling/GBAAppStyle.h"

#include "Misc/EngineVersionComparison.h"

#if UE_VERSION_NEWER_THAN(5, 1, -1)
#include "Styling/AppStyle.h"
#else
#include "EditorStyleSet.h"
#endif

const FSlateBrush* FGBAAppStyle::GetBrush(const FName& InPropertyName, const ANSICHAR* InSpecifier)
{
#if UE_VERSION_NEWER_THAN(5, 1, -1)
	return FAppStyle::GetBrush(InPropertyName, InSpecifier);
#else
	return FEditorStyle::GetBrush(InPropertyName, InSpecifier);
#endif
}

FSlateFontInfo FGBAAppStyle::GetFontStyle(const FName& InPropertyName, const ANSICHAR* InSpecifier)
{
#if UE_VERSION_NEWER_THAN(5, 1, -1)
	return FAppStyle::GetFontStyle(InPropertyName, InSpecifier);
#else
	return FEditorStyle::GetFontStyle(InPropertyName, InSpecifier);
#endif
}
