// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#include "AssetTypes/GBAAssetTypeActions_AttributeSet.h"

#include "Abilities/GBAAttributeSetBlueprintBase.h"
#include "AssetTypes/GBABlueprintFactory.h"
#include "Editor/GBABlueprintEditor.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "GBAAssetTypeActions_AttributeSet"

FGBAAssetTypeActions_AttributeSet::FGBAAssetTypeActions_AttributeSet(const EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

void FGBAAssetTypeActions_AttributeSet::OpenAssetEditor(const TArray<UObject*>& InObjects, const TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UBlueprint* Blueprint = Cast<UBlueprint>(*ObjIt))
		{
			const TSharedRef<FGBABlueprintEditor> NewEditor(new FGBABlueprintEditor());

			TArray<UBlueprint*> Blueprints;
			Blueprints.Add(Blueprint);

			NewEditor->InitAttributeSetEditor(Mode, EditWithinLevelEditor, Blueprints, false);
		}
		else
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("FailedToLoadAttributeSetBlueprint", "Attribute Set Blueprint could not be loaded because it derives from an invalid class. Check to make sure the parent class for this blueprint hasn't been removed!"));
		}
	}
}

const TArray<FText>& FGBAAssetTypeActions_AttributeSet::GetSubMenus() const
{
	static const TArray SubMenus
	{
		LOCTEXT("AssetTypeActions_BlueprintAttributesSubMenu", "Gameplay Blueprint Attributes")
	};

	return SubMenus;
}

UFactory* FGBAAssetTypeActions_AttributeSet::GetFactoryForBlueprintType(UBlueprint* InBlueprint) const
{
	check(InBlueprint && InBlueprint->IsA(UGBAAttributeSetBlueprint::StaticClass()));
	UGBABlueprintFactory* Factory = NewObject<UGBABlueprintFactory>();
	Factory->ParentClass = TSubclassOf<UGBAAttributeSetBlueprintBase>(*InBlueprint->GeneratedClass);
	return Factory;
}

#undef LOCTEXT_NAMESPACE
