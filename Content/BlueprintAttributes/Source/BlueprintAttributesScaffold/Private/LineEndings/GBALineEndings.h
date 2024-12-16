// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "Containers/UnrealString.h"

namespace GBA::String
{
	/** Replaces all Line Endings with "\n" line terminator */
	FString FromHostLineEndings(const FString& InString);
	FString FromHostLineEndings(FString&& InString);
	void FromHostLineEndingsInline(FString& InString);

	/** Replaces all Line Endings with the host platform line terminator */
	FString ToHostLineEndings(const FString& InString);
	FString ToHostLineEndings(FString&& InString);
	void ToHostLineEndingsInline(FString& InString);

} // UE::String
