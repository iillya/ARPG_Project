// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

BLUEPRINTATTRIBUTES_API DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintAttributes, Display, All);

#define GBA_LOG(Verbosity, Format, ...) \
{ \
    UE_LOG(LogBlueprintAttributes, Verbosity, Format, ##__VA_ARGS__); \
}

#define GBA_NS_LOG(Verbosity, Format, ...) \
{ \
    UE_LOG(LogBlueprintAttributes, Verbosity, TEXT("%s - %s"), *FString(__FUNCTION__), *FString::Printf(Format, ##__VA_ARGS__)); \
}