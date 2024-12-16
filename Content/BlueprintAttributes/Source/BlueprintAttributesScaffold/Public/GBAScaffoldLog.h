// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

BLUEPRINTATTRIBUTESSCAFFOLD_API DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintAttributesScaffold, Display, All);

#define GBA_SCAFFOLD_LOG(Verbosity, Format, ...) \
{ \
    UE_LOG(LogBlueprintAttributesScaffold, Verbosity, Format, ##__VA_ARGS__); \
}
