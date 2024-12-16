// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class BLUEPRINTATTRIBUTESEDITORCOMMON_API FGBAEditorStyle : public FSlateStyleSet
{
public:
	FGBAEditorStyle();
	virtual ~FGBAEditorStyle() override;

	static FGBAEditorStyle& Get()
	{
		static FGBAEditorStyle Inst;
		return Inst;
	}
};
