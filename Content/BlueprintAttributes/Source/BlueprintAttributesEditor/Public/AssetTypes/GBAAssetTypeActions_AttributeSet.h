// Copyright 2022-2024 Mickael Daniel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions/AssetTypeActions_Blueprint.h"
#include "Blueprint/GBAAttributeSetBlueprint.h"

class FGBAAssetTypeActions_AttributeSet : public FAssetTypeActions_Blueprint
{
public:
	explicit FGBAAssetTypeActions_AttributeSet(EAssetTypeCategories::Type InAssetCategory);

	// IAssetTypeActions Implementation
	virtual FText GetName() const override
	{
		return NSLOCTEXT("AssetTypeActions", "GBAAssetTypeActions_AttributeSet", "Gameplay Blueprint Attribute Set");
	}

	virtual FColor GetTypeColor() const override
	{
		return FColor(0, 87, 96);
	}
	
	virtual UClass* GetSupportedClass() const override
	{
		return UGBAAttributeSetBlueprint::StaticClass();
	}
	
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override
	{
		return AssetCategory;
	}

	virtual const TArray<FText>& GetSubMenus() const override;
	
	// virtual uint32 GetCategories() override { return EAssetTypeCategories::Gameplay; }
	// virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;
	// virtual void PerformAssetDiff(UObject* Asset1, UObject* Asset2, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override;

	// FAssetTypeActions_Blueprint interface
	virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;

private:
	EAssetTypeCategories::Type AssetCategory;
};
