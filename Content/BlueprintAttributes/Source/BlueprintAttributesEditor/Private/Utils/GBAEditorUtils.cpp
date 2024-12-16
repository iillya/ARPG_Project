// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "Utils/GBAEditorUtils.h"

#include "AttributeSet.h"
#include "DetailLayoutBuilder.h"
#include "Editor.h"
#include "Editor/GBABlueprintEditor.h"
#include "Misc/EngineVersionComparison.h"
#include "Subsystems/AssetEditorSubsystem.h"

UAttributeSet* UE::GBA::EditorUtils::GetAttributeBeingCustomized(const IDetailLayoutBuilder& InDetailLayout)
{
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	InDetailLayout.GetObjectsBeingCustomized(ObjectsBeingCustomized);

	TArray<UAttributeSet*> AttributeSetsBeingCustomized;
	for (TWeakObjectPtr<UObject> ObjectBeingCustomized : ObjectsBeingCustomized)
	{
		if (UAttributeSet* AttributeSet = Cast<UAttributeSet>(ObjectBeingCustomized.Get()))
		{
			AttributeSetsBeingCustomized.Add(AttributeSet);
		}
	}

	return AttributeSetsBeingCustomized.IsValidIndex(0) ? AttributeSetsBeingCustomized[0] : nullptr;
}

UBlueprint* UE::GBA::EditorUtils::GetBlueprintFromClass(const UClass* InClass)
{
	if (!InClass)
	{
		return nullptr;
	}

	return Cast<UBlueprint>(InClass->ClassGeneratedBy);
}

TWeakPtr<FGBABlueprintEditor> UE::GBA::EditorUtils::FindBlueprintEditorForAsset(UObject* InObject)
{
	if (!GEditor || !IsValid(InObject))
	{
		return nullptr;
	}

	UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
	if (!IsValid(AssetEditorSubsystem))
	{
		return nullptr;
	}

	IAssetEditorInstance* EditorInstance = AssetEditorSubsystem->FindEditorForAsset(InObject, false);
	if (!EditorInstance)
	{
		return nullptr;
	}

	FGBABlueprintEditor* BlueprintEditor = StaticCast<FGBABlueprintEditor*>(EditorInstance);
	if (!BlueprintEditor)
	{
		return nullptr;
	}
#if UE_VERSION_NEWER_THAN(5, 1, -1)
	return StaticCastWeakPtr<FGBABlueprintEditor>(BlueprintEditor->AsWeak());
#else
	TWeakPtr<FGBABlueprintEditor> WeakPtr(StaticCastSharedRef<FGBABlueprintEditor>(BlueprintEditor->AsShared()));
	return WeakPtr;
#endif
}
