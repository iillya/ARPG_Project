// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "GBALineEndings.h"

#include "CoreTypes.h"
#include "Misc/CString.h"
#include "Templates/UnrealTemplate.h"

namespace GBA::String
{
	FString FromHostLineEndings(const FString& InString)
	{
		FString New = InString;
		FromHostLineEndingsInline(New);
		return New;
	}

	FString FromHostLineEndings(FString&& InString)
	{
		FromHostLineEndingsInline(InString);
		return MoveTemp(InString);
	}

	void FromHostLineEndingsInline(FString& InString)
	{
		InString.ReplaceInline(TEXT("\r\n"), TEXT("\n"));
		InString.ReplaceInline(TEXT("\r"), TEXT("\n"));
	}

	FString ToHostLineEndings(const FString& InString)
	{
		FString New = InString;
		ToHostLineEndingsInline(New);
		return New;
	}

	FString ToHostLineEndings(FString&& InString)
	{
		ToHostLineEndingsInline(InString);
		return MoveTemp(InString);
	}

	void ToHostLineEndingsInline(FString& InString)
	{
		FromHostLineEndingsInline(InString);

		if (TCString<TCHAR>::Strcmp(TEXT("\n"), LINE_TERMINATOR) != 0)
		{
			InString.ReplaceInline(TEXT("\n"), LINE_TERMINATOR);
		}
	}
} // UE::String
