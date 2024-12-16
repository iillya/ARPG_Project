// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "AttributeSet.h"
#include "EdGraphUtilities.h"
#include "EdGraphSchema_K2.h"
#include "SGBAGameplayAttributeGraphPin.h"
#include "SGraphPin.h"

class FGBAGraphPanelPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override
	{
		// TODO: Pass down containing owner to SGBAGameplayAttributeGraphPin to be able to list only owned attributes
		// FBlueprintEditorUtils::FindBlueprintForNode(UEdGraphNode*)
		if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct
			&& InPin->PinType.PinSubCategoryObject == FGameplayAttribute::StaticStruct()
			&& InPin->Direction == EGPD_Input)
		{
			return SNew(SGBAGameplayAttributeGraphPin, InPin);
		}
		
		return nullptr;
	}
};
