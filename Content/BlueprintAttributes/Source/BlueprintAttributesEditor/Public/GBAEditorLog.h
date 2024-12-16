// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

BLUEPRINTATTRIBUTESEDITOR_API DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintAttributesEditor, Display, All);

#define GBA_EDITOR_LOG(Verbosity, Format, ...) \
{ \
    UE_LOG(LogBlueprintAttributesEditor, Verbosity, Format, ##__VA_ARGS__); \
}

#define GBA_EDITOR_NS_LOG(Verbosity, Format, ...) \
{ \
    UE_LOG(LogBlueprintAttributesEditor, Verbosity, TEXT("%s - %s"), *FString(__FUNCTION__), *FString::Printf(Format, ##__VA_ARGS__)); \
}